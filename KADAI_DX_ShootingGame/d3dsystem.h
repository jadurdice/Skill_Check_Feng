#ifndef _D3DSYSTEM_H_
#define _D3DSYSTEM_H_


bool D3DInit(HWND hWnd);
void D3DUninit(void);

LPDIRECT3DDEVICE9 GetDevice(void);

#endif