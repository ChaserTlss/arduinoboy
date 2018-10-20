struct cell {
	axis_t x;
	axis_t y;
};

struct cellStack {
	len_t len;
	struct cell** cell;
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

/*
 *Let the center of the block at x,y
 *To make the rotation more natural
 */
struct block {
	axis_t x;
	axis_t y;
	enum blockType type;
	struct cellStack cells;
};

struct russianBlock {
	len_t score;
	struct block* wait_block;
	struct block* fall_block;
	struct cellStack cells;
};

enum LF_RT {
	LEFT_TR = 1,
	RIGHT_TR = 2,
};

enum DIRECTION {
	LEFT_MV = 1,
	RIGHT_MV = 2,
	UP_MV = 3,
	DOWN_MV = 4,
};

#define SUCCESS 0
#define CANTPUT 1
