#ifndef _GPXE_SETTINGS_H
#define _GPXE_SETTINGS_H

/** @file
 *
 * Configuration settings
 *
 */

#include <stdint.h>
#include <gpxe/dhcp.h>
#include <gpxe/tables.h>

struct config_setting;

/**
 * A configuration context
 *
 * This identifies the context within which settings are inspected and
 * changed.  For example, the context might be global, or might be
 * restricted to the settings stored in NVS on a particular device.
 */
struct config_context {
	/** DHCP options block, or NULL
	 *
	 * If NULL, all registered DHCP options blocks will be used.
	 */
	struct dhcp_option_block *options;
};

/**
 * A configuration setting type
 *
 * This represents a type of configuration setting (e.g. string, IPv4
 * address, etc.).
 */
struct config_setting_type {
	/** Name
	 *
	 * This is the name exposed to the user (e.g. "string").
	 */
	const char *name;
	/** Show value of setting
	 *
	 * @v context		Configuration context
	 * @v setting		Configuration setting
	 * @ret value		Setting value (as a string), or NULL
	 */
	const char * ( * show ) ( struct config_context *context,
				  struct config_setting *setting );
	/** Set value of setting
	 *
	 * @v context		Configuration context
	 * @v setting		Configuration setting
	 * @v value		Setting value (as a string)
	 * @ret rc		Return status code
	 */ 
	int ( * set ) ( struct config_context *context,
			struct config_setting *setting,
			const char *value );
};

/** Declare a configuration setting type */
#define	__config_setting_type __table ( config_setting_types, 01 )

/**
 * A configuration setting
 *
 * This represents a single configuration setting (e.g. "hostname").
 */
struct config_setting {
	/** Name
	 *
	 * This is the human-readable name for the setting.  Where
	 * possible, it should match the name used in dhcpd.conf (see
	 * dhcp-options(5)).
	 */
	const char *name;
	/** DHCP option tag
	 *
	 * This is the DHCP tag used to identify the option in DHCP
	 * packets and stored option blocks.
	 */
	unsigned int tag;
	/** Configuration setting type
	 *
	 * This identifies the type of setting (e.g. string, IPv4
	 * address, etc.).
	 */
	struct config_setting_type *type;
};

/** Declare a configuration setting */
#define	__config_setting __table ( config_settings, 01 )

/* Function prototypes */

extern const char * ( show_setting ) ( struct config_context *context,
				       const char *name );
extern int ( set_setting ) ( struct config_context *context, const char *name,
			     const char *value );

#endif /* _GPXE_SETTINGS_H */