#include <stdlib.h>

#include "russianBlock.h"

struct cell* cellConstructor( axis_t x, axis_t y )
{
	struct cell* temp = (struct cell*)malloc( sizeof(struct cell) );
	if (temp == NULL)
		return NULL;
	temp->x = x;
	temp->y = y;
	return temp;
}

void cellDestroy( struct cell* this )
{
	free( this );
}

unsigned cellHash( struct cell* this )
{
	return this->y*mapWidth + this->x;
}

struct cell* cellStackFind( struct cellStack* this, len_t begin, len_t end, unsigned hash )
{
	while (begin < end){
		len_t mid = (begin + end)/2;
		if (this->cell[mid] > hash){
			begin = mid + 1;
		} else if (this->cell[mid] < hash){
			end = mid - 1;
		} else {
			return this->cell[mid];
		}
	}
	return this->cell[begin];
}

bool cellStackExist( struct cellStack* this, unsigned hash )
{
	struct cell* temp = cellStackFind( this, 0, this->len-1, hash );
	return cellHash( temp ) == hash;
}

void blockDestroy( struct block* this )
{
	int i = 0;
	for (i = 0; i < this->cells.len; i++){
		cellDestroy(this->cells.cell[i]);
	}
	free( this );
}

struct block* blockConstructor( enum blockType type )
{
	struct block* temp == (struct block*)malloc( sizeof(struct block) );
	if (temp == NULL)
		return NULL;

	temp->type = type;
	switch (type){
		case LONG_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellConstructor( 0, 2 );// +
			temp->cells.cell[1] = cellConstructor( 0, 1 );// +
			temp->cells.cell[2] = cellConstructor( 0, 0 );// *
			temp->cells.cell[3] = cellConstructor( 0,-1 );// +
			break;
		case TRIA_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellConstructor(-1, 0 );//+*+
			temp->cells.cell[1] = cellConstructor( 0, 0 );// +
			temp->cells.cell[2] = cellConstructor( 1, 0 );
			temp->cells.cell[3] = cellConstructor( 0,-1 );
			break;
		case LF_Z_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellConstructor(-1, 0 );//+*
			temp->cells.cell[1] = cellConstructor( 0, 0 );// ++
			temp->cells.cell[2] = cellConstructor( 0,-1 );
			temp->cells.cell[3] = cellConstructor( 1,-1 );
			break;
		case RT_Z_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellConstructor( 0, 0 );// *+
			temp->cells.cell[1] = cellConstructor( 1, 0 );//++
			temp->cells.cell[2] = cellConstructor(-1,-1 );
			temp->cells.cell[3] = cellConstructor( 0,-1 );
			break;
		case LF_L_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellConstructor( 0, 1 );//+
			temp->cells.cell[1] = cellConstructor( 0, 0 );//*
			temp->cells.cell[2] = cellConstructor( 0,-1 );//++
			temp->cells.cell[3] = cellConstructor( 1,-1 );
			break;
		case RT_L_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellConstructor( 0, 1 );// +
			temp->cells.cell[1] = cellConstructor( 0, 0 );// *
			temp->cells.cell[2] = cellConstructor( 0,-1 );//++
			temp->cells.cell[3] = cellConstructor(-1,-1 );
			break;
		case SQUA_BLOCK:
			temp->cells.len = 4;
			temp->cells.cell[0] = cellConstructor( 0, 0 );//*+
			temp->cells.cell[1] = cellConstructor( 1, 0 );//++
			temp->cells.cell[2] = cellConstructor( 0,-1 );
			temp->cells.cell[3] = cellConstructor(-1,-1 );
			break;
		default:
			game_log( "Can't find block type %d\n", type );
			goto ERROR_BLOCK_MALLOC;
	};

	return temp;
ERROR_BLOCK_MALLOC:
	blockDestroy( temp );
	return NULL;
}

unsigned blockHash( const struct block* this )
{
	return this->y*mapWidth + this->x;
}

unsigned blockCellHash( const struct block* this, len_t cellIndex )
{
	return cellHash( this->cells.cell[cellIndex] ) + blockHase( this );
}

bool blockCanPut( const struct block* this, const struct cellStack* cells )
{
	//if every cell that in this* is not exist in cells 
	//then return True
	int i = 0;
	for (i = 0; i < this->cells.len; i++){
		unsigned cellHashTemp = blockCellHash( this, i );
		if (cellStackExist( cells, cellHashTemp ))
			return FALSE;
	}
	return TRUE;
}

struct block* blockCpy( const struct block* this )
{
	struct block* temp = (struct block*)malloc( sizeof(struct block) );
	temp->x = this->x;
	temp->y = this->y;
	temp->type = this->type;
	temp->cells.len = this->cells.len;

	int i = 0;
	for (i = 0; i < temp->cell.len; i++){
		temp->cells.cell[i] = cellConstructor( this->cells.cell[i]->x,
						this->cells.cell[i]->y );
	}
}

void blockTurn( struct block* this, enum LF_RT flag )
{
	int i = 0;
	if (flag > RIGHT_TR || flag < LEFT_TR)
		return ;
	for (i = 0; i < this->cells.len; i++){
		axis_t tempAxis = this->cells.cell[i]->x;
		this->cells.cell[i]->x = this->cells.cell[i]->y
				* (flag == LEFT_TR)?(-1):(1);

		this->cells.cell[i]->y = tempAxis
				* (flag == RIGHT_TR)?(-1):(1);
	}
}

int blockTurn&Put( struct block* this, enum LF_RT flag, const struct cellStack* cells )
{
	blockTurn( this, flag );
	if (!blockCanPut( this, cells )){
		blockTurn( this, flag == LEFT_TR ? RIGHT_TR : LEFT_TR );
		return CANTPUT;
	}
	return SUCCESS;
}

void blockMove( struct block* this, enum DIRECTION flag )
{
	if (flag < LEFT_MV || flag > DOWN_MV)
		return ;
	switch (flag){
		case LEFT_MV:
			break;
		case RIGHT_MV:
			break;
		case UP_MV:
			break;
		case DOWN_MV:
			break;
		default:
			break;
	}
}

int blockMove&Put( struct block* this,
		enum DIRECTION flag,
		const struct cellStack* cells )
{
	blockMove( this, flag );
	if (!blockCanPut( this, cells )){
		switch (flag){
			case LEFT_MV:
				blockMove( this, RIGHT_MV );
				break;
			case RIGHT_MV:
				blockMove( this, LEFT_MV );
				break;
			case UP_MV:
				blockMove( this, DOWN_MV );
				break;
			case DOWN_MV:
				blockMove( this, UP_MV );
				break;
			default:
				break;
		}
		return CANTPUT;
	}
	return SUCCESS;
}

bool blockIsPlaced( const struct block* this, const struct cellStack* cells )
{

}
