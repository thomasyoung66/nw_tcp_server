/***********************************************************************

    Copyright 2006 Ma Bingyao

    These sources is free software. Redistributions of source code must
    retain the above copyright notice. Redistributions in binary form
    must reproduce the above copyright notice. You can redistribute it
    freely. You can use it with any free or commercial software.

    These sources is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY. Without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

        You may contact the author by:
           e-mail:  andot@coolcode.cn

*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xxtea.h"

void xxtea_long_encrypt(xxtea_long *v, xxtea_long len, xxtea_long *k) {
    xxtea_long n = len - 1;
    xxtea_long z = v[n], y = v[0], p, q = 6 + 52 / (n + 1), sum = 0, e;
    if (n < 1) {
        return;
    }
    while (0 < q--) {
        sum += XXTEA_DELTA;
        e = sum >> 2 & 3;
        for (p = 0; p < n; p++) {
            y = v[p + 1];
            z = v[p] += XXTEA_MX;
        }
        y = v[0];
        z = v[n] += XXTEA_MX;
    }
}

void xxtea_long_decrypt(xxtea_long *v, xxtea_long len, xxtea_long *k) {
    xxtea_long n = len - 1;
    xxtea_long z = v[n], y = v[0], p, q = 6 + 52 / (n + 1), sum = q * XXTEA_DELTA, e;
    if (n < 1) {
        return;
    }
    while (sum != 0) {
        e = sum >> 2 & 3;
        for (p = n; p > 0; p--) {
            z = v[p - 1];
            y = v[p] -= XXTEA_MX;
        }
        z = v[n];
        y = v[0] -= XXTEA_MX;
        sum -= XXTEA_DELTA;
    }
}


static xxtea_long *xxtea_to_long_array(unsigned char *data, xxtea_long len, int include_length, xxtea_long *ret_len) {
    xxtea_long i, n, *result;
	n = len >> 2;
    n = (((len & 3) == 0) ? n : n + 1);
    if (include_length) {
        result = (xxtea_long *)malloc((n + 1) << 2);
        result[n] = len;
	    *ret_len = n + 1;
	} else {
        result = (xxtea_long *)malloc(n << 2);
	    *ret_len = n;
    }
	memset(result, 0, n << 2);
	for (i = 0; i < len; i++) {
        result[i >> 2] |= (xxtea_long)data[i] << ((i & 3) << 3);
    }
    return result;
}

static unsigned char *xxtea_to_byte_array(xxtea_long *data, xxtea_long len, int include_length, xxtea_long *ret_len) {
    xxtea_long i, n, m;
    unsigned char *result;
    n = len << 2;
    if (include_length) {
        m = data[len - 1];
        if ((m < n - 7) || (m > n - 4)) return NULL;
        n = m;
    }
    result = (unsigned char *)malloc(n + 1);
	for (i = 0; i < n; i++) {
        result[i] = (unsigned char)((data[i >> 2] >> ((i & 3) << 3)) & 0xff);
    }
	result[n] = '\0';
	*ret_len = n;
	return result;
}

static unsigned char *php_xxtea_encrypt(unsigned char *data, xxtea_long len, unsigned char *key, xxtea_long *ret_len) {
    unsigned char *result;
    xxtea_long *v, *k, v_len, k_len;
    v = xxtea_to_long_array(data, len, 1, &v_len);
    k = xxtea_to_long_array(key, 16, 0, &k_len);
    xxtea_long_encrypt(v, v_len, k);
    result = xxtea_to_byte_array(v, v_len, 0, ret_len);
    free(v);
    free(k);
    return result;
}

static unsigned char *php_xxtea_decrypt(unsigned char *data, xxtea_long len, unsigned char *key, xxtea_long *ret_len) {
    unsigned char *result;
    xxtea_long *v, *k, v_len, k_len;
    v = xxtea_to_long_array(data, len, 0, &v_len);
    k = xxtea_to_long_array(key, 16, 0, &k_len);
    xxtea_long_decrypt(v, v_len, k);
    result = xxtea_to_byte_array(v, v_len, 1, ret_len);
    free(v);
    free(k);
    return result;
}

char * xxtea_encrypt( unsigned char *data,int data_len,unsigned char * key,int * out_length)
{
    unsigned char *result;
    xxtea_long   ret_length;
	char key1[64];
	memset(key1,0x00,sizeof(key1));
	strcpy(key1,key);
	
	if (data==NULL || data_len<=0|| key==NULL || strlen(key)==0)
		return NULL;
/*
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &data, &data_len, &key, &key_len) == FAILURE) {
        return;
    }*/
//	if (data_len == 0) RETVAL_STRINGL(NULL, 0, 0);
 //   if (key_len != 16) RETURN_FALSE;
    result = php_xxtea_encrypt(data, data_len/*data_len*/, key1, &ret_length);
    if (result != NULL) {
		*out_length=ret_length;
		return (char * )result;
        //RETVAL_STRINGL((char *)result, ret_length, 0);
    } else {
		*out_length=0;
		return NULL;
      //  RETURN_FALSE;
    }
}
/* }}} */


/* {{{ proto string xxtea_decrypt(string data, string key)
   Decrypt string using XXTEA algorithm */
char * xxtea_decrypt(unsigned char *data,int data_len,unsigned char * key,int * out_length)
{
  //  unsigned char *data, *key;
    unsigned char *result;
    xxtea_long  ret_length;
	
	char key1[64];
	memset(key1,0x00,sizeof(key1));
	strcpy(key1,key);

	if (data==NULL || data_len<=0|| key==NULL || strlen(key)==0)
		return NULL;
    //if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &data, &data_len, &key, &key_len) == FAILURE) {
     //   return;
    //}
	//if (data_len == 0) RETVAL_STRINGL(NULL, 0, 0);
    //if (key_len != 16) RETURN_FALSE;
    result = php_xxtea_decrypt(data, data_len, key1, &ret_length);
    if (result != NULL) {
		*out_length=ret_length;
		return (char * )result;
		//RETVAL_STRINGL((char *)result, ret_length, 0);
    } else {
		*out_length=0;
        return NULL;
    }
}
