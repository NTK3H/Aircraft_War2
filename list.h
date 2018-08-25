/* Date:	2018/6/5
 * Author:	Truth <2568878009@qq.com>
 */

#ifndef __FN_LIST_H
#define __FN_LIST_H

#include <stdio.h>
#include <stdlib.h>

#ifndef	LIST_TYPE
#define LIST_TYPE	int
#endif

#ifdef LIST_SUPPORT_HASHMAP
#include <string.h>
#endif

typedef struct _list_struct_mem{
	LIST_TYPE mem;
	struct _list_struct_mem *next;
}mlist;

#pragma pack(push,4)
#ifdef LIST_SUPPORT_HASHMAP
typedef struct _list_hash_map{
	int index;
	char *str;
	struct _list_hash_map *last;
	struct _list_hash_map *next;
}mhp;
#endif

typedef struct _list_struct_head{
	int size;
#ifdef LIST_SUPPORT_HASHMAP
	int hashsize;
	mhp *hashmap;
#endif
	mlist *first;
}list;
#pragma pack(pop)

list *list_init()
{
	list *init = (list*)malloc(sizeof(list));
	init->size = 0;
	init->first = NULL;
	return init;
}

LIST_TYPE list_var(list *nlist, int index)
{
	if(index>nlist->size)return 0;
	mlist *m = nlist->first;
	for(int i=0;i<index;i++)
		m = m->next;
	return m->mem;
}

int list_insert(list *nlist, LIST_TYPE iMem, int index)
{
	if(index>nlist->size)return 0;
	if(nlist->size == 0)
	{
		nlist->first = (mlist*)malloc(sizeof(mlist));
		nlist->first->mem = iMem;
		nlist->size++;
		return 1;
	}
	if(index == 0)
	{
		mlist *m_bkf = nlist->first;
		nlist->first = (mlist*)malloc(sizeof(mlist));
		nlist->first->mem = iMem;
		nlist->first->next = m_bkf;
		nlist->size++;
		return 1;
	}
	mlist *m = nlist->first;
	for(int i=1;i<index;i++)
		m = m->next;
	mlist *m_bkf = m->next;
	m->next = (mlist*)malloc(sizeof(mlist));
	m = m->next;
	m->mem = iMem;
	m->next = m_bkf;
	nlist->size++;
	return 1;
}

void list_push_back(list *nlist, LIST_TYPE iMem)
{
	list_insert(nlist,iMem,nlist->size);
}

void list_push_front(list *nlist, LIST_TYPE iMem)
{
	list_insert(nlist,iMem,0);
}

int list_size(list *nlist)
{
	if(nlist == NULL)return 0;
	return nlist->size;
}

int list_erase(list *nlist, int size, int index)
{
	if(index>nlist->size)return 0;
	mlist *m = nlist->first;
	if(index == 0)
	{
		for(int i=0;i<size;i++)
		{
			nlist->first = nlist->first->next;
			free(m);
			m = nlist->first;
		}
		nlist->size-=size;
		return 1;
	}
	for(int i=1;i<index;i++)
		m = m->next;
	mlist *m_bkf;
	for(int i=0;i<size;i++)
	{
		m_bkf = m->next;
		m->next = m_bkf->next;
		free(m_bkf);
	}
	nlist->size-=size;
	return 1;
}

int list_change(list *nlist, LIST_TYPE iNewMem, int index)
{
	if(index>nlist->size)return 0;
	mlist *m = nlist->first;
	for(int i=0;i<index;i++)
		m = m->next;
	m->mem = iNewMem;
	return 1;
}

int list_indexof(list *nlist, LIST_TYPE iMem)
{
	int index = 0;
	int flag = -1;
	mlist *m = nlist->first;
	for(int i=0;i<nlist->size;i++)
	{
		if(m->mem == iMem)
		{
			flag++;
			break;
		}
		m = m->next;
		index++;
	}
	return flag == -1?flag:index;
}

int list_last_indexof(list *nlist, LIST_TYPE iMem)
{
	int index = 0;
	int flag = -1;
	int index_flag = 0;
	mlist *m = nlist->first;
	for(int i=0;i<nlist->size;i++)
	{
		if(m->mem == iMem)
		{
			flag++;
			index_flag=0;
		}
		else
			index_flag++;
		m = m->next;
		index++;
	}
	return flag == -1?flag:index-index_flag-1;
}

int *list_listtoarray(list *nlist)
{
	int *iArr = (int*)malloc(sizeof(int)*nlist->size);
	mlist *m = nlist->first;
	for(int i=0;i<nlist->size;i++)
	{
		iArr[i] = (int)m->mem;
		m = m->next;
	}
	return iArr;
}

list *list_arraytolist(int *arr, int size)
{
	list *nlist = list_init();
	for(int i=0;i<size;i++)
		list_push_back(nlist,(LIST_TYPE)arr[i]);
	return nlist;
}

mlist *list_begin(list *nlist)
{
	return nlist->first;
}

mlist *list_end(list *nlist)
{
	mlist *m = nlist->first;
	for(int i=0;i<nlist->size;i++)
		m = m->next;
	return m;
}

void list_swap(list *xlist, list *ylist)
{
	list *bkf = xlist;
	xlist = ylist;
	ylist = bkf;
}

int list_test(list *nlist, LIST_TYPE var, int index)
{
	if(index>nlist->size)return 0;
	mlist *m = nlist->first;
	for(int i=0;i<index;i++)
		m = m->next;
	return var==m->mem;
}

void list_clear(list *nlist)
{
	list_erase(nlist,0,nlist->size);
	nlist = NULL;
}

int list_empty(list *nlist)
{
	if(nlist == NULL) return 0;
	return nlist->first == NULL;
}

void list_delete(list *nlist)
{
	list_clear(nlist);
	free(nlist);
	nlist = NULL;
}

#endif
