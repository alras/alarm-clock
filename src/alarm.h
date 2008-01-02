/*
 * Copyright/Licensing information.
 */

#ifndef ALARM_H_
#define ALARM_H_

#include <glib-object.h>
#include <gconf/gconf-client.h>

G_BEGIN_DECLS

/*
 * Structure definitions
 */

typedef enum {
	ALARM_TYPE_INVALID = 0,
	ALARM_TYPE_CLOCK,		/* Alarm at specific time */
	ALARM_TYPE_TIMER		/* Alarm in X mins */
} AlarmType;

typedef enum {
	ALARM_NOTIFY_INVALID = 0,
	ALARM_NOTIFY_SOUND,		/* Notification by sound */
	ALARM_NOTIFY_COMMAND,	/* Notification by command */
} AlarmNotifyType;

typedef struct _Alarm Alarm;
typedef struct _AlarmClass AlarmClass;

struct _Alarm {
	GObject parent;
	
	gchar *gconf_dir;		/* GConf directory */
	guint id;				/* Alarm ID */
	/* Alarm */
/*	time_t	 alarm;
	gchar	*message;
	gboolean started;*/
	
	/* Notification */
/*	AlarmNotifyType	 notify_type;
	gboolean		 notify_sound_loop;
	gchar			*notify_sound;
	gchar			*notify_command;*/
};

struct _AlarmClass {
	GObjectClass parent;
	
	/* Signals */
	
};

static GConfEnumStringPair alarm_type_enum_map [];
static GConfEnumStringPair alarm_notify_type_enum_map [];

/*
 * Utility macros
 */

#define TYPE_ALARM (alarm_get_type())

#define ALARM(object) \
  (G_TYPE_CHECK_INSTANCE_CAST((object), TYPE_ALARM, Alarm))

#define ALARM_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), TYPE_ALARM, AlarmClass))

#define IS_ALARM(object) \
  (G_TYPE_CHECK_INSTANCE_TYPE((object), TYPE_ALARM))

#define IS_ALARM_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), TYPE_ALARM))

#define ALARM_GET_CLASS(object) \
  (G_TYPE_INSTANCE_GET_CLASS((object), TYPE_ALARM, AlarmClass))


/* 
 * Failsafe defaults for use when the schema isn't found
 * or doesn't provide sensible defaults
 */
#define ALARM_DEFAULT_TYPE			ALARM_TYPE_CLOCK
#define ALARM_DEFAULT_TIME			(time (NULL) + 60 * 5)
#define ALARM_DEFAULT_MESSAGE		"Alarm!"
#define ALARM_DEFAULT_NOTIFY_TYPE	ALARM_NOTIFY_SOUND
#define ALARM_DEFAULT_SOUND_FILE	""				// Should default to first in stock sound list
#define ALARM_DEFAULT_SOUND_LOOP	TRUE
#define ALARM_DEFAULT_COMMAND		""				// Should default to first in app list

/*
 * Function prototypes.
 */

/* used by ALARM_TYPE */
GType 
alarm_get_type (void);

gchar *
alarm_gconf_get_full_key (Alarm *alarm, const gchar *key);


const gchar *
alarm_type_to_string (AlarmType type);

AlarmType 
alarm_type_from_string (const gchar *type);


const gchar *
alarm_notify_type_to_string (AlarmNotifyType type);

AlarmNotifyType 
alarm_notify_type_from_string (const gchar *type);



/* <internal> */

static void alarm_class_init (AlarmClass *class);

/* Prototypes and constants for property manipulation */
static void alarm_set_property(GObject *object,
                               guint prop_id,
                               const GValue *value,
                               GParamSpec *pspec);

static void alarm_get_property(GObject *object,
                               guint prop_id,
                               GValue *value,
                               GParamSpec *pspec);

/*
 * Method definitions.
 */



G_END_DECLS

#endif /*ALARM_H_*/
