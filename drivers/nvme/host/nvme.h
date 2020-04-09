/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2011-2014, Intel Corporation.
 */

#ifndef _NVME_H
#define _NVME_H

#include <linux/nvme.h>
#include <linux/cdev.h>
#include <linux/pci.h>
#include <linux/kref.h>
#include <linux/blk-mq.h>
#include <linux/lightnvm.h>
#include <linux/sed-opal.h>
#include <linux/fault-inject.h>
#include <linux/rcupdate.h>
#include <linux/wait.h>

#include <trace/events/block.h>

extern unsigned int nvme_io_timeout;
#define NVME_IO_TIMEOUT	(nvme_io_timeout * HZ)

extern unsigned int admin_timeout;
#define ADMIN_TIMEOUT	(admin_timeout * HZ)

#define NVME_DEFAULT_KATO	5
#define NVME_KATO_GRACE		10

extern struct workqueue_struct *nvme_wq;
extern struct workqueue_struct *nvme_reset_wq;
extern struct workqueue_struct *nvme_delete_wq;

enum {
	NVME_NS_LBA		= 0,
	NVME_NS_LIGHTNVM	= 1,
};

/*
 * List of workarounds for devices that required behavior not specified in
 * the standard.
 */
enum nvme_quirks {
	/*
	 * Prefers I/O aligned to a stripe size specified in a vendor
	 * specific Identify field.
	 */
	NVME_QUIRK_STRIPE_SIZE			= (1 << 0),

	/*
	 * The controller doesn't handle Identify value others than 0 or 1
	 * correctly.
	 */
	NVME_QUIRK_IDENTIFY_CNS			= (1 << 1),

	/*
	 * The controller deterministically returns O's on reads to
	 * logical blocks that deallocate was called on.
	 */
	NVME_QUIRK_DEALLOCATE_ZEROES		= (1 << 2),

	/*
	 * The controller needs a delay before starts checking the device
	 * readiness, which is done by reading the NVME_CSTS_RDY bit.
	 */
	NVME_QUIRK_DELAY_BEFORE_CHK_RDY		= (1 << 3),

	/*
	 * APST should not be used.
	 */
	NVME_QUIRK_NO_APST			= (1 << 4),

	/*
	 * The deepest sleep state should not be used.
	 */
	NVME_QUIRK_NO_DEEPEST_PS		= (1 << 5),

	/*
	 * Supports the LighNVM command set if indicated in vs[1].
	 */
	NVME_QUIRK_LIGHTNVM			= (1 << 6),

	/*
	 * Set MEDIUM priority on SQ creation
	 */
	NVME_QUIRK_MEDIUM_PRIO_SQ		= (1 << 7),

	/*
	 * Ignore device provided subnqn.
	 */
	NVME_QUIRK_IGNORE_DEV_SUBNQN		= (1 << 8),

	/*
	 * Broken Write Zeroes.
	 */
	NVME_QUIRK_DISABLE_WRITE_ZEROES		= (1 << 9),

	/*
	 * Force simple suspend/resume path.
	 */
	NVME_QUIRK_SIMPLE_SUSPEND		= (1 << 10),

	/*
	 * Use only one interrupt vector for all queues
	 */
	NVME_QUIRK_SINGLE_VECTOR		= (1 << 11),

	/*
	 * Use non-standard 128 bytes SQEs.
	 */
	NVME_QUIRK_128_BYTES_SQES		= (1 << 12),

	/*
	 * Prevent tag overlap between queues
	 */
	NVME_QUIRK_SHARED_TAGS                  = (1 << 13),

	/*
	 * The controller doesn't handle the Identify Namespace
	 * Identification Descriptor list subcommand despite claiming
	 * NVMe 1.3 compliance.
	 */
	NVME_QUIRK_NO_NS_DESC_LIST		= (1 << 15),
};

/*
 * Common request structure for NVMe passthrough.  All drivers must have
 * this structure as the first member of their request-private data.
 */
struct nvme_request {
	struct nvme_command	*cmd;
	union nvme_result	result;
	u8			retries;
	u8			flags;
	u16			status;
	struct nvme_ctrl	*ctrl;
};

/*
 * Mark a bio as coming in through the mpath node.
 */
#define REQ_NVME_MPATH		REQ_DRV

enum {
	NVME_REQ_CANCELLED		= (1 << 0),
	NVME_REQ_USERCMD		= (1 << 1),
};

static inline struct nvme_request *nvme_req(struct request *req)
{
	return blk_mq_rq_to_pdu(req);
}

static inline u16 nvme_req_qid(struct request *req)
{
	if (!req->rq_disk)
		return 0;
	return blk_mq_unique_tag_to_hwq(blk_mq_unique_tag(req)) + 1;
}

/* The below value is the specific amount of delay needed before checking
 * readiness in case of the PCI_DEVICE(0x1c58, 0x0003), which needs the
 * NVME_QUIRK_DELAY_BEFORE_CHK_RDY quirk enabled. The value (in ms) was
 * found empirically.
 */
#define NVME_QUIRK_DELAY_AMOUNT		2300

enum nvme_ctrl_state {
	NVME_CTRL_NEW,
	NVME_CTRL_LIVE,
	NVME_CTRL_RESETTING,
	NVME_CTRL_CONNECTING,
	NVME_CTRL_DELETING,
	NVME_CTRL_DEAD,
};

struct nvme_fault_inject {
#ifdef CONFIG_FAULT_INJECTION_DEBUG_FS
	struct fault_attr attr;
	struct dentry *parent;
	bool dont_retry;	/* DNR, do not retry */
	u16 status;		/* status code */
#endif
};

struct nvme_ctrl {
	bool comp_seen;
	enum nvme_ctrl_state state;
	bool identified;
	spinlock_t lock;
	struct mutex scan_lock;
	const struct nvme_ctrl_ops *ops;
	struct request_queue *admin_q;
	struct request_queue *connect_q;
	struct request_queue *fabrics_q;
	struct device *dev;
	int instance;
	int numa_node;
	struct blk_mq_tag_set *tagset;
	struct blk_mq_tag_set *admin_tagset;
	struct list_head namespaces;
	struct rw_semaphore namespaces_rwsem;
	struct device ctrl_device;
	struct device *device;	/* char device */
	struct cdev cdev;
	struct work_struct reset_work;
	struct work_struct delete_work;
	wait_queue_head_t state_wq;

	struct nvme_subsystem *subsys;
	struct list_head subsys_entry;

	struct opal_dev *opal_dev;

	char name[12];
	u16 cntlid;

	u32 ctrl_config;
	u16 mtfa;
	u32 queue_count;

	u64 cap;
	u32 page_size;
	u32 max_hw_sectors;
	u32 max_segments;
	u16 crdt[3];
	u16 oncs;
	u16 oacs;
	u16 nssa;
	u16 nr_streams;
	u16 sqsize;
	u32 max_namespaces;
	atomic_t abort_limit;
	u8 vwc;
	u32 vs;
	u32 sgls;
	u16 kas;
	u8 npss;
	u8 apsta;
	u32 oaes;
	u32 aen_result;
	u32 ctratt;
	unsigned int shutdown_timeout;
	unsigned int kato;
	bool subsystem;
	unsigned long quirks;
	struct nvme_id_power_state psd[32];
	struct nvme_effects_log *effects;
	struct work_struct scan_work;
	struct work_struct async_event_work;
	struct delayed_work ka_work;
	struct nvme_command ka_cmd;
	struct work_struct fw_act_work;
	unsigned long events;
	bool created;

#ifdef CONFIG_NVME_MULTIPATH
	/* asymmetric namespace access: */
	u8 anacap;
	u8 anatt;
	u32 anagrpmax;
	u32 nanagrpid;
	struct mutex ana_lock;
	struct nvme_ana_rsp_hdr *ana_log_buf;
	size_t ana_log_size;
	struct timer_list anatt_timer;
	struct work_struct ana_work;
#endif

	/* Power saving configuration */
	u64 ps_max_latency_us;
	bool apst_enabled;

	/* PCIe only: */
	u32 hmpre;
	u32 hmmin;
	u32 hmminds;
	u16 hmmaxd;

	/* Fabrics only */
	u32 ioccsz;
	u32 iorcsz;
	u16 icdoff;
	u16 maxcmd;
	int nr_reconnects;
	struct nvmf_ctrl_options *opts;

	struct page *discard_page;
	unsigned long discard_page_busy;

	struct nvme_fault_inject fault_inject;
};

enum nvme_iopolicy {
	NVME_IOPOLICY_NUMA,
	NVME_IOPOLICY_RR,
};

struct nvme_subsystem {
	int			instance;
	struct device		dev;
	/*
	 * Because we unregister the device on the last put we need
	 * a separate refcount.
	 */
	struct kref		ref;
	struct list_head	entry;
	struct mutex		lock;
	struct list_head	ctrls;
	struct list_head	nsheads;
	char			subnqn[NVMF_NQN_SIZE];
	char			serial[20];
	char			model[40];
	char			firmware_rev[8];
	u8			cmic;
	u16			vendor_id;
	u16			awupf;	/* 0's based awupf value. */
	struct ida		ns_ida;
#ifdef CONFIG_NVME_MULTIPATH
	enum nvme_iopolicy	iopolicy;
#endif
};

/*
 * Container structure for uniqueue namespace identifiers.
 */
struct nvme_ns_ids {
	u8	eui64[8];
	u8	nguid[16];
	uuid_t	uuid;
};

/*
 * Anchor structure for namespaces.  There is one for each namespace in a
 * NVMe subsystem that any of our controllers can see, and the namespace
 * structure for each controller is chained of it.  For private namespaces
 * there is a 1:1 relation to our namespace structures, that is ->list
 * only ever has a single entry for private namespaces.
 */
struct nvme_ns_head {
	struct list_head	list;
	struct srcu_struct      srcu;
	struct nvme_subsystem	*subsys;
	unsigned		ns_id;
	struct nvme_ns_ids	ids;
	struct list_head	entry;
	struct kref		ref;
	int			instance;
#ifdef CONFIG_NVME_MULTIPATH
	struct gendisk		*disk;
	struct bio_list		requeue_list;
	spinlock_t		requeue_lock;
	struct work_struct	requeue_work;
	struct mutex		lock;
	unsigned long		flags;
#define NVME_NSHEAD_DISK_LIVE	0
	struct nvme_ns __rcu	*current_path[];
#endif
};

struct nvme_ns {
	struct list_head list;

	struct nvme_ctrl *ctrl;
	struct request_queue *queue;
	struct gendisk *disk;
#ifdef CONFIG_NVME_MULTIPATH
	enum nvme_ana_state ana_state;
	u32 ana_grpid;
#endif
	struct list_head siblings;
	struct nvm_dev *ndev;
	struct kref kref;
	struct nvme_ns_head *head;

	int lba_shift;
	u16 ms;
	u16 sgs;
	u32 sws;
	bool ext;
	u8 pi_type;
	unsigned long flags;
#define NVME_NS_REMOVING	0
#define NVME_NS_DEAD     	1
#define NVME_NS_ANA_PENDING	2

	struct nvme_fault_inject fault_inject;

};

struct nvme_ctrl_ops {
	const char *name;
	struct module *module;
	unsigned int flags;
#define NVME_F_FABRICS			(1 << 0)
#define NVME_F_METADATA_SUPPORTED	(1 << 1)
#define NVME_F_PCI_P2PDMA		(1 << 2)
	int (*reg_read32)(struct nvme_ctrl *ctrl, u32 off, u32 *val);
	int (*reg_write32)(struct nvme_ctrl *ctrl, u32 off, u32 val);
	int (*reg_read64)(struct nvme_ctrl *ctrl, u32 off, u64 *val);
	void (*free_ctrl)(struct nvme_ctrl *ctrl);
	void (*submit_async_event)(struct nvme_ctrl *ctrl);
	void (*delete_ctrl)(struct nvme_ctrl *ctrl);
	int (*get_address)(struct nvme_ctrl *ctrl, char *buf, int size);
};

#ifdef CONFIG_FAULT_INJECTION_DEBUG_FS
void nvme_fault_inject_init(struct nvme_fault_inject *fault_inj,
			    const char *dev_name);
void nvme_fault_inject_fini(struct nvme_fault_inject *fault_inject);
void nvme_should_fail(struct request *req);
#else
static inline void nvme_fault_inject_init(struct nvme_fault_inject *fault_inj,
					  const char *dev_name)
{
}
static inline void nvme_fault_inject_fini(struct nvme_fault_inject *fault_inj)
{
}
static inline void nvme_should_fail(struct request *req) {}
#endif

static inline int nvme_reset_subsystem(struct nvme_ctrl *ctrl)
{
	if (!ctrl->subsystem)
		return -ENOTTY;
	return ctrl->ops->reg_write32(ctrl, NVME_REG_NSSR, 0x4E564D65);
}

/*
 * Convert a 512B sector number to a device logical block number.
 */
static inline u64 nvme_sect_to_lba(struct nvme_ns *ns, sector_t sector)
{
	return sector >> (ns->lba_shift - SECTOR_SHIFT);
}

/*
 * Convert a device logical block number to a 512B sector number.
 */
static inline sector_t nvme_lba_to_sect(struct nvme_ns *ns, u64 lba)
{
	return lba << (ns->lba_shift - SECTOR_SHIFT);
}

static inline void nvme_end_request(struct request *req, __le16 status,
		union nvme_result result)
{
	struct nvme_request *rq = nvme_req(req);

	rq->status = le16_to_cpu(status) >> 1;
	rq->result = result;
	/* inject error when permitted by fault injection framework */
	nvme_should_fail(req);
	blk_mq_complete_request(req);
}

static inline void nvme_get_ctrl(struct nvme_ctrl *ctrl)
{
	get_device(ctrl->device);
}

static inline void nvme_put_ctrl(struct nvme_ctrl *ctrl)
{
	put_device(ctrl->device);
}

void nvme_complete_rq(struct request *req);
bool nvme_cancel_request(struct request *req, void *data, bool reserved);
bool nvme_change_ctrl_state(struct nvme_ctrl *ctrl,
		enum nvme_ctrl_state new_state);
bool nvme_wait_reset(struct nvme_ctrl *ctrl);
int nvme_disable_ctrl(struct nvme_ctrl *ctrl);
int nvme_enable_ctrl(struct nvme_ctrl *ctrl);
int nvme_shutdown_ctrl(struct nvme_ctrl *ctrl);
int nvme_init_ctrl(struct nvme_ctrl *ctrl, struct device *dev,
		const struct nvme_ctrl_ops *ops, unsigned long quirks);
void nvme_uninit_ctrl(struct nvme_ctrl *ctrl);
void nvme_start_ctrl(struct nvme_ctrl *ctrl);
void nvme_stop_ctrl(struct nvme_ctrl *ctrl);
void nvme_put_ctrl(struct nvme_ctrl *ctrl);
int nvme_init_identify(struct nvme_ctrl *ctrl);

void nvme_remove_namespaces(struct nvme_ctrl *ctrl);

int nvme_sec_submit(void *data, u16 spsp, u8 secp, void *buffer, size_t len,
		bool send);

void nvme_complete_async_event(struct nvme_ctrl *ctrl, __le16 status,
		volatile union nvme_result *res);

void nvme_stop_queues(struct nvme_ctrl *ctrl);
void nvme_start_queues(struct nvme_ctrl *ctrl);
void nvme_kill_queues(struct nvme_ctrl *ctrl);
void nvme_sync_queues(struct nvme_ctrl *ctrl);
void nvme_unfreeze(struct nvme_ctrl *ctrl);
void nvme_wait_freeze(struct nvme_ctrl *ctrl);
int nvme_wait_freeze_timeout(struct nvme_ctrl *ctrl, long timeout);
void nvme_start_freeze(struct nvme_ctrl *ctrl);

#define NVME_QID_ANY -1
struct request *nvme_alloc_request(struct request_queue *q,
		struct nvme_command *cmd, blk_mq_req_flags_t flags, int qid);
void nvme_cleanup_cmd(struct request *req);
blk_status_t nvme_setup_cmd(struct nvme_ns *ns, struct request *req,
		struct nvme_command *cmd);
int nvme_submit_sync_cmd(struct request_queue *q, struct nvme_command *cmd,
		void *buf, unsigned bufflen);
int __nvme_submit_sync_cmd(struct request_queue *q, struct nvme_command *cmd,
		union nvme_result *result, void *buffer, unsigned bufflen,
		unsigned timeout, int qid, int at_head,
		blk_mq_req_flags_t flags, bool poll);
int nvme_set_features(struct nvme_ctrl *dev, unsigned int fid,
		      unsigned int dword11, void *buffer, size_t buflen,
		      u32 *result);
int nvme_get_features(struct nvme_ctrl *dev, unsigned int fid,
		      unsigned int dword11, void *buffer, size_t buflen,
		      u32 *result);
int nvme_set_queue_count(struct nvme_ctrl *ctrl, int *count);
void nvme_stop_keep_alive(struct nvme_ctrl *ctrl);
int nvme_reset_ctrl(struct nvme_ctrl *ctrl);
int nvme_reset_ctrl_sync(struct nvme_ctrl *ctrl);
int nvme_try_sched_reset(struct nvme_ctrl *ctrl);
int nvme_delete_ctrl(struct nvme_ctrl *ctrl);

int nvme_get_log(struct nvme_ctrl *ctrl, u32 nsid, u8 log_page, u8 lsp,
		void *log, size_t size, u64 offset);

extern const struct attribute_group *nvme_ns_id_attr_groups[];
extern const struct block_device_operations nvme_ns_head_ops;

#ifdef CONFIG_NVME_MULTIPATH
static inline bool nvme_ctrl_use_ana(struct nvme_ctrl *ctrl)
{
	return ctrl->ana_log_buf != NULL;
}

void nvme_mpath_unfreeze(struct nvme_subsystem *subsys);
void nvme_mpath_wait_freeze(struct nvme_subsystem *subsys);
void nvme_mpath_start_freeze(struct nvme_subsystem *subsys);
void nvme_set_disk_name(char *disk_name, struct nvme_ns *ns,
			struct nvme_ctrl *ctrl, int *flags);
bool nvme_failover_req(struct request *req);
void nvme_kick_requeue_lists(struct nvme_ctrl *ctrl);
int nvme_mpath_alloc_disk(struct nvme_ctrl *ctrl,struct nvme_ns_head *head);
void nvme_mpath_add_disk(struct nvme_ns *ns, struct nvme_id_ns *id);
void nvme_mpath_remove_disk(struct nvme_ns_head *head);
int nvme_mpath_init(struct nvme_ctrl *ctrl, struct nvme_id_ctrl *id);
void nvme_mpath_uninit(struct nvme_ctrl *ctrl);
void nvme_mpath_stop(struct nvme_ctrl *ctrl);
bool nvme_mpath_clear_current_path(struct nvme_ns *ns);
void nvme_mpath_clear_ctrl_paths(struct nvme_ctrl *ctrl);
struct nvme_ns *nvme_find_path(struct nvme_ns_head *head);

static inline void nvme_mpath_check_last_path(struct nvme_ns *ns)
{
	struct nvme_ns_head *head = ns->head;

	if (head->disk && list_empty(&head->list))
		kblockd_schedule_work(&head->requeue_work);
}

static inline void nvme_trace_bio_complete(struct request *req,
        blk_status_t status)
{
	struct nvme_ns *ns = req->q->queuedata;

	if (req->cmd_flags & REQ_NVME_MPATH)
		trace_block_bio_complete(ns->head->disk->queue,
					 req->bio, status);
}

static inline void nvme_mpath_update_disk_size(struct gendisk *disk)
{
	struct block_device *bdev = bdget_disk(disk, 0);

	if (bdev) {
		bd_set_size(bdev, get_capacity(disk) << SECTOR_SHIFT);
		bdput(bdev);
	}
}

extern struct device_attribute dev_attr_ana_grpid;
extern struct device_attribute dev_attr_ana_state;
extern struct device_attribute subsys_attr_iopolicy;

#else
static inline bool nvme_ctrl_use_ana(struct nvme_ctrl *ctrl)
{
	return false;
}
/*
 * Without the multipath code enabled, multiple controller per subsystems are
 * visible as devices and thus we cannot use the subsystem instance.
 */
static inline void nvme_set_disk_name(char *disk_name, struct nvme_ns *ns,
				      struct nvme_ctrl *ctrl, int *flags)
{
	sprintf(disk_name, "nvme%dn%d", ctrl->instance, ns->head->instance);
}

static inline bool nvme_failover_req(struct request *req)
{
	return false;
}
static inline void nvme_kick_requeue_lists(struct nvme_ctrl *ctrl)
{
}
static inline int nvme_mpath_alloc_disk(struct nvme_ctrl *ctrl,
		struct nvme_ns_head *head)
{
	return 0;
}
static inline void nvme_mpath_add_disk(struct nvme_ns *ns,
		struct nvme_id_ns *id)
{
}
static inline void nvme_mpath_remove_disk(struct nvme_ns_head *head)
{
}
static inline bool nvme_mpath_clear_current_path(struct nvme_ns *ns)
{
	return false;
}
static inline void nvme_mpath_clear_ctrl_paths(struct nvme_ctrl *ctrl)
{
}
static inline void nvme_mpath_check_last_path(struct nvme_ns *ns)
{
}
static inline void nvme_trace_bio_complete(struct request *req,
        blk_status_t status)
{
}
static inline int nvme_mpath_init(struct nvme_ctrl *ctrl,
		struct nvme_id_ctrl *id)
{
	if (ctrl->subsys->cmic & (1 << 3))
		dev_warn(ctrl->device,
"Please enable CONFIG_NVME_MULTIPATH for full support of multi-port devices.\n");
	return 0;
}
static inline void nvme_mpath_uninit(struct nvme_ctrl *ctrl)
{
}
static inline void nvme_mpath_stop(struct nvme_ctrl *ctrl)
{
}
static inline void nvme_mpath_unfreeze(struct nvme_subsystem *subsys)
{
}
static inline void nvme_mpath_wait_freeze(struct nvme_subsystem *subsys)
{
}
static inline void nvme_mpath_start_freeze(struct nvme_subsystem *subsys)
{
}
static inline void nvme_mpath_update_disk_size(struct gendisk *disk)
{
}
#endif /* CONFIG_NVME_MULTIPATH */

#ifdef CONFIG_NVM
int nvme_nvm_register(struct nvme_ns *ns, char *disk_name, int node);
void nvme_nvm_unregister(struct nvme_ns *ns);
extern const struct attribute_group nvme_nvm_attr_group;
int nvme_nvm_ioctl(struct nvme_ns *ns, unsigned int cmd, unsigned long arg);
#else
static inline int nvme_nvm_register(struct nvme_ns *ns, char *disk_name,
				    int node)
{
	return 0;
}

static inline void nvme_nvm_unregister(struct nvme_ns *ns) {};
static inline int nvme_nvm_ioctl(struct nvme_ns *ns, unsigned int cmd,
							unsigned long arg)
{
	return -ENOTTY;
}
#endif /* CONFIG_NVM */

static inline struct nvme_ns *nvme_get_ns_from_dev(struct device *dev)
{
	return dev_to_disk(dev)->private_data;
}

#endif /* _NVME_H */
