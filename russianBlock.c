#include <stdio.h>

struct cell* cellCreate( axis_t x, axis_t y )
{
	struct cell* temp = malloc( sizeof(struct cell) );
	if (temp == NULL)
		return NULL;
	temp->x = x;
	temp->y = y;
	return temp;
}

void cellDestroy( struct cell* this )
{
	free(this);
}

void blockDestroy( struct block* this )
{
	free(this);
}

struct block* blockCreate( enum blockType type )
{
	struct block* temp == malloc( sizeof(struct block) );
	if (temp == NULL)
		return NULL;
	switch (type){
		case LONG_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellCreate( 0, 0 );// +
			temp->cells.cell[1] = cellCreate( 0, 1 );// +
			temp->cells.cell[2] = cellCreate( 0, 2 );// +
			temp->cells.cell[3] = cellCreate( 0, 3 );// +
			break;
		case TRIA_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellCreate( 0, 0 );//+++
			temp->cells.cell[1] = cellCreate( 1, 0 );// +
			temp->cells.cell[2] = cellCreate( 2, 0 );
			temp->cells.cell[3] = cellCreate( 1, 1 );
			break;
		case LF_Z_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellCreate( 0, 0 );//++
			temp->cells.cell[1] = cellCreate( 1, 0 );// ++
			temp->cells.cell[2] = cellCreate( 1, 1 );
			temp->cells.cell[3] = cellCreate( 2, 1 );
			break;
		case RT_Z_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellCreate( 1, 0 );// ++
			temp->cells.cell[1] = cellCreate( 2, 0 );//++
			temp->cells.cell[2] = cellCreate( 0, 1 );
			temp->cells.cell[3] = cellCreate( 1, 1 );
			break;
		case LF_L_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellCreate( 0, 0 );//+
			temp->cells.cell[1] = cellCreate( 0, 1 );//+
			temp->cells.cell[2] = cellCreate( 0, 2 );//++
			temp->cells.cell[3] = cellCreate( 1, 2 );
			break;
		case RT_L_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellCreate( 1, 0 );// +
			temp->cells.cell[1] = cellCreate( 1, 1 );// +
			temp->cells.cell[2] = cellCreate( 0, 2 );//++
			temp->cells.cell[3] = cellCreate( 1, 2 );
			break;
		case SQUA_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellCreate( 0, 0 );//++
			temp->cells.cell[1] = cellCreate( 1, 0 );//++
			temp->cells.cell[2] = cellCreate( 0, 1 );
			temp->cells.cell[3] = cellCreate( 1, 1 );
			break;
		default:
			game_log("Can't find block type %d\n", type);
			goto ERROR_BLOCK_MALLOC;
	};

	return temp;
ERROR_BLOCK_MALLOC:
	blockDestroy( temp );
	return NULL;
}
