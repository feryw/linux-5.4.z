{
	"bounds checks mixing signed and unsigned, positive bounds",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 7),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, 2),
	BPF_JMP_REG(BPF_JGE, BPF_REG_2, BPF_REG_1, 3),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_1, 4, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.errstr = "unbounded min value",
	.errstr_unpriv = "R1 has unknown scalar with mixed signed bounds",
	.result = REJECT,
},
{
	"bounds checks mixing signed and unsigned",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 7),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, -1),
	BPF_JMP_REG(BPF_JGT, BPF_REG_1, BPF_REG_2, 3),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_1, 1, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.errstr = "unbounded min value",
	.errstr_unpriv = "R1 has unknown scalar with mixed signed bounds",
	.result = REJECT,
},
{
	"bounds checks mixing signed and unsigned, variant 2",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 9),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, -1),
	BPF_JMP_REG(BPF_JGT, BPF_REG_1, BPF_REG_2, 5),
	BPF_MOV64_IMM(BPF_REG_8, 0),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_8, BPF_REG_1),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_8, 1, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_8),
	BPF_ST_MEM(BPF_B, BPF_REG_8, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.errstr = "unbounded min value",
	.errstr_unpriv = "R8 has unknown scalar with mixed signed bounds",
	.result = REJECT,
},
{
	"bounds checks mixing signed and unsigned, variant 3",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 8),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, -1),
	BPF_JMP_REG(BPF_JGT, BPF_REG_1, BPF_REG_2, 4),
	BPF_MOV64_REG(BPF_REG_8, BPF_REG_1),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_8, 1, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_8),
	BPF_ST_MEM(BPF_B, BPF_REG_8, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.errstr = "unbounded min value",
	.errstr_unpriv = "R8 has unknown scalar with mixed signed bounds",
	.result = REJECT,
},
{
	"bounds checks mixing signed and unsigned, variant 4",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 7),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, 1),
	BPF_ALU64_REG(BPF_AND, BPF_REG_1, BPF_REG_2),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_1, 1, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.result = ACCEPT,
},
{
	"bounds checks mixing signed and unsigned, variant 5",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 9),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, -1),
	BPF_JMP_REG(BPF_JGT, BPF_REG_1, BPF_REG_2, 5),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_1, 1, 4),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 4),
	BPF_ALU64_REG(BPF_SUB, BPF_REG_0, BPF_REG_1),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.errstr = "unbounded min value",
	.errstr_unpriv = "R1 has unknown scalar with mixed signed bounds",
	.result = REJECT,
},
{
	"bounds checks mixing signed and unsigned, variant 6",
	.insns = {
	BPF_MOV64_IMM(BPF_REG_2, 0),
	BPF_MOV64_REG(BPF_REG_3, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_3, -512),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_4, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_6, -1),
	BPF_JMP_REG(BPF_JGT, BPF_REG_4, BPF_REG_6, 5),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_4, 1, 4),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, 1),
	BPF_MOV64_IMM(BPF_REG_5, 0),
	BPF_ST_MEM(BPF_H, BPF_REG_10, -512, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_skb_load_bytes),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.errstr = "R4 min value is negative, either use unsigned",
	.result = REJECT,
},
{
	"bounds checks mixing signed and unsigned, variant 7",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 7),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, 1024 * 1024 * 1024),
	BPF_JMP_REG(BPF_JGT, BPF_REG_1, BPF_REG_2, 3),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_1, 1, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.result = ACCEPT,
},
{
	"bounds checks mixing signed and unsigned, variant 8",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 9),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, -1),
	BPF_JMP_REG(BPF_JGT, BPF_REG_2, BPF_REG_1, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_1, 1, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.errstr = "unbounded min value",
	.errstr_unpriv = "R1 has unknown scalar with mixed signed bounds",
	.result = REJECT,
},
{
	"bounds checks mixing signed and unsigned, variant 9",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 10),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_LD_IMM64(BPF_REG_2, -9223372036854775808ULL),
	BPF_JMP_REG(BPF_JGT, BPF_REG_2, BPF_REG_1, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_1, 1, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.result = ACCEPT,
},
{
	"bounds checks mixing signed and unsigned, variant 10",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 9),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, 0),
	BPF_JMP_REG(BPF_JGT, BPF_REG_2, BPF_REG_1, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_1, 1, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.errstr = "unbounded min value",
	.errstr_unpriv = "R1 has unknown scalar with mixed signed bounds",
	.result = REJECT,
},
{
	"bounds checks mixing signed and unsigned, variant 11",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 9),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, -1),
	BPF_JMP_REG(BPF_JGE, BPF_REG_2, BPF_REG_1, 2),
	/* Dead branch. */
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_1, 1, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.errstr = "unbounded min value",
	.errstr_unpriv = "R1 has unknown scalar with mixed signed bounds",
	.result = REJECT,
},
{
	"bounds checks mixing signed and unsigned, variant 12",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 9),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, -6),
	BPF_JMP_REG(BPF_JGE, BPF_REG_2, BPF_REG_1, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_1, 1, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.errstr = "unbounded min value",
	.errstr_unpriv = "R1 has unknown scalar with mixed signed bounds",
	.result = REJECT,
},
{
	"bounds checks mixing signed and unsigned, variant 13",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 6),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, 2),
	BPF_JMP_REG(BPF_JGE, BPF_REG_2, BPF_REG_1, 2),
	BPF_MOV64_IMM(BPF_REG_7, 1),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_7, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_7, BPF_REG_1),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_7, 4, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_7),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.errstr = "unbounded min value",
	.errstr_unpriv = "R7 has unknown scalar with mixed signed bounds",
	.result = REJECT,
},
{
	"bounds checks mixing signed and unsigned, variant 14",
	.insns = {
	BPF_LDX_MEM(BPF_W, BPF_REG_9, BPF_REG_1,
		    offsetof(struct __sk_buff, mark)),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 8),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, -1),
	BPF_MOV64_IMM(BPF_REG_8, 2),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_9, 42, 6),
	BPF_JMP_REG(BPF_JSGT, BPF_REG_8, BPF_REG_1, 3),
	BPF_JMP_IMM(BPF_JSGT, BPF_REG_1, 1, 2),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_REG(BPF_JGT, BPF_REG_1, BPF_REG_2, -3),
	BPF_JMP_IMM(BPF_JA, 0, 0, -7),
	},
	.fixup_map_hash_8b = { 4 },
	.errstr = "unbounded min value",
	.errstr_unpriv = "R1 has unknown scalar with mixed signed bounds",
	.result = REJECT,
},
{
	"bounds checks mixing signed and unsigned, variant 15",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 4),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, -8),
	BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -16),
	BPF_MOV64_IMM(BPF_REG_2, -6),
	BPF_JMP_REG(BPF_JGE, BPF_REG_2, BPF_REG_1, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
	BPF_JMP_IMM(BPF_JGT, BPF_REG_0, 1, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_ST_MEM(BPF_B, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_hash_8b = { 3 },
	.errstr = "unbounded min value",
	.errstr_unpriv = "R1 has unknown scalar with mixed signed bounds",
	.result = REJECT,
	.result_unpriv = REJECT,
},
