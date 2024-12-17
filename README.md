# rtscheduler
Real-time scheduler with bootloader

# Using the configuration file

The first line in the configuration file details the number of tasks in the task set. The following lines detail colon separated task initialization values, in the following order:

```
TASK NUMBER:TYPE:EXECUTION TIME:PERIOD:REFRESH:DEADLINE:OFFSET
```

For values that are not applicable (such as refresh), use `NULL`. The `TYPE` field can be one of:
+ `periodic`
+ `aperiodic`
+ `sporadic`