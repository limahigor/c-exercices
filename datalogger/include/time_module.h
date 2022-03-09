#ifndef TIME_MODULE_H
#define TIME_MODULE_H

typedef struct count_s *count_h;
typedef struct clock_s *clock_h;

gboolean count_init(count_h *timer);
gboolean count_free(count_h timer);
char *get_count_string(count_h timer);
int get_total_seconds(count_h count);
int get_count_second(count_h count);
int get_count_minute(count_h count);

void get_time(struct tm **atual);
char *get_time_string();
char *get_date_string();

#endif