#ifndef _GPXE_REFCNT_H
#define _GPXE_REFCNT_H

/** @file
 *
 * Reference counting
 *
 */

/**
 * A reference counter
 *
 * This data structure is designed to be embedded within a
 * reference-counted object.
 */
struct refcnt {
	/** Current reference count
	 *
	 * When this count is decremented below zero, the free()
	 * method will be called.
	 */
	int refcnt;
	/** Free containing object
	 *
	 * This method is called when the reference count is
	 * decremented below zero.
	 *
	 * If this method is left NULL, the standard library free()
	 * function will be called.  The upshot of this is that you
	 * may omit the free() method if the @c refcnt object is the
	 * first element of your reference-counted struct.
	 */
	void ( * free ) ( struct refcnt *refcnt );
};

extern void ref_get ( struct refcnt *refcnt );
extern void ref_put ( struct refcnt *refcnt );

#endif /* _GPXE_REFCNT_H */