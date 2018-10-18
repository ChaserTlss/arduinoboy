struct cell {
	axis_t x;
	axis_t y;
};

struct cellStack {
	len_t len;
	struct cell** cell;
};

struct block {
	axis_t x;
	axis_t y;
	struct cellStack cells;
};

struct russianBlock {
	len_t score;
	struct block* wait_block;
	struct block* fall_block;
	struct cellStack cells;
};

enum blockType {
	LONG_BLOCK = 1,
	TRIA_BLOCK = 2,
	LF_Z_BLOCK = 3,
	RT_Z_BLOCK = 4,
	LF_L_BLOCK = 5,
	RT_L_BLOCK = 6,
	SQUA_BLOCK = 7,
};
