### pmacct [IP traffic accounting : BGP : BMP : RPKI : IGP : Streaming Telemetry]

### pmacct is Copyright (C) 2003-2021 by Paolo Lucente


# TABLE OF CONTENTS:
* I.	Daemons and plugins included with pmacct distribution
* II.	Configuring pmacct for compilation and installing
* III.	Brief SQL (MySQL, PostgreSQL, SQLite 3.x) setup examples
* IV.	Running the libpcap-based daemon (pmacctd)
* V.	Running the NetFlow/IPFIX and sFlow daemons (nfacctd/sfacctd)
* VI.	Running the NFLOG-based daemon (uacctd)
* VII.	Running the pmacct IMT client (pmacct)
* VIII.	Running the RabbitMQ/AMQP plugin
* IX.	Running the Kafka plugin
* X.	Internal buffering and queueing
* XI.	Quickstart guide to packet/flow classification
* XII.	Quickstart guide to setup a NetFlow/IPFIX agent/probe 
* XIII.	Quickstart guide to setup a sFlow agent/probe 
* XIV.	Quickstart guide to setup the BGP daemon
* XV.	Quickstart guide to setup a NetFlow/IPFIX/sFlow replicator
* XVI.	Quickstart guide to setup the IS-IS daemon
* XVII.	Quickstart guide to setup the BMP daemon
* XVIII.	Quickstart guide to setup Streaming Telemetry collection 
* XIX.	Running the print plugin to write to flat-files
* XX.	Quickstart guide to setup GeoIP lookups
* XXI.	Using pmacct as traffic/event logger
* XXII.   Connecting pmacct to a Redis cache
* XXIII.	Miscellaneous notes and troubleshooting tips


# I. Daemons and plugins included with pmacct distribution

All traffic accounting daemons can print statistics to stdout, keep them in
memory tables, store persistently to open-source RDBMS (MySQL, PostgreSQL,
Sqlite 3) or to noSQL databates (ie. BerkeleyDB) and to flat-files, and
publish to AMQP and Kafka brokers (typically to insert in ElasticSearch,
InfluxDB, Druid, ClickHouse and, more in general, all backends which are not
natively supported by pmacct). BGP, BMP and Streaming Telemetry daemons can
publish control and infrastructure planes to AMQP and Kafka brokers. This is
a list of the daemons included in the pmacct distribution: 

## pmacctd 

libpcap-based accounting daemon: it captures packets from one or multiple interfaces it is bound to. Other than acting as a collector, this daemon can also export statistics via NetFlow, IPFIX and sFlow protocols.
 
## nfacctd

NetFlow/IPFIX accounting daemon: it listens for NetFlow v5/v9 and IPFIX packets on one or more interfaces (IPv4 and IPv6). Other than acting as a collector, this daemon can also replicate to 3rd party collectors.

## sfacctd

sFlow accounting daemon; it listens for sFlow packets v2, v4 and v5 on one or more interfaces (both IPv4 and IPv6). Other than acting as a collector, this daemon can also replicate to 3rd party collectors.

## uacctd

Linux Netlink NFLOG accounting daemon; it captures packets by leveraging a NFLOG multicast group - and works only on Linux. Other than acting as a collector, this daemon can also export statistics via NetFlow, IPFIX and sFlow protocols.

## pmtelemetryd

Standalone Streaming Telemetry collector daemon; listens for telemetry data binding to a TCP or UDP port and logs real-time and/or dumps at regular time-intervals to configured backends.

## pmbgpd

Standalone BGP collector daemon; acts as a passive iBGP or eBGP neighbor and maintains per-peer RIBs; can log real-time and/or dump at regular time-intervals BGP data to configured backends.

## pmbmpd

Standalone BMP collector daemon; can log real-time and/or dump at regular time-intervals BMP/BGP data to configured backends.

## pmacct

Commandline pmacct client; it allows to retrieve data from a memory table plugin; it can perform queries over data or do bulk data retrieval. Output is formatted, CSV or JSON format.  Suitable for data injection in 3rd party tools like RRDtool, Gnuplot or SNMP server among the others.

Given its open and pluggable architecture, pmacct is easily extensible with new plugins. Here is a list of traffic accounting plugins included in the official pmacct distribution:

## memory
Data is stored in a memory table and can be fetched via the pmacct command-line client tool, 'pmacct'. This plugin also implements a push model and allows easily to inject data into 3rd party tools. The plugin is recommended for prototyping and proof-of-concept (without mass traffic generation) and smaller-scale / home production environments and is compiled in by default.

## mysql

A working MySQL/MariaDB installation can be used for data storage. This plugin can be compiled using the *--enable-mysql* switch. 

## pgsql

A working PostgreSQL installation can be used for data storage. This plugin can be compiled using the *--enable-pgsql* switch.

## sqlite3

A working SQLite 3.x or BerkeleyDB 5.x (compiled in with the SQLite API) installation can be used for data storage. This plugin can be compiled using the *--enable-sqlite3* switch.

## print

Data is printed at regular intervals to flat-files or standard output in tab-spaced, CSV and JSON formats. This plugin is compiled in by default.

## amqp

Data is sent to a RabbitMQ broker, running AMQP protocol, for delivery to consumer applications or tools. Popular consumers are ElasticSearch, InfluxDB, Druid and ClickHouse. This plugin can be compiled using the *--enable-rabbitmq* switch.

## kafka
Data is sent to a Kafka broker for delivery to consumer applications or tools. Popular consumers are ElasticSearch, InfluxDB, Druid and ClickHouse. This plugin can be compiled using the *--enable-kafka* switch.

## tee
Applies to nfacctd and sfacctd daemons only. It's a featureful packet replicator for NetFlow/IPFIX/sFlow data. This plugin is compiled in by default.


## nfprobe
Applies to pmacctd and uacctd daemons only. Exports collected data via NetFlow v5/v9 or IPFIX. This plugin is compiled in by default.

## sfprobe
applies to pmacctd and uacctd daemons only. Exports collected data via sFlow v5. This plugin is compiled in by default.


# II. Configuring pmacct for compilation and installing

The simplest way to configure the package for compilation is to download the latest stable released tarball from http://www.pmacct.net/ and let the configure script to probe default headers and libraries for you. The only dependency that pmacct brings is libpcap library and headers: libpcap-dev on Debian/Ubuntu, libpcap-devel on CentOS/RHEL (note: this may need enabling extra yum repos!) or (self-compiled) equivalent must be installed on the system. Then, a first round of guessing is done via pkg-config then, for some libraries, "typical" default locations are checked, ie. /usr/local/lib. Switches one likely wants enabled are already set so, ie. 64 bits counters and multi-threading (pre- requisite for the BGP, BMP, and IGP daemon codes); the full list of switches enabled by default are marked as 'default: yes' in the "./configure --help" output. SQL plugins, AMQP and Kafka support are all disabled by default instead. A few examples will follow; to get the list of available switches, you can use the following command-line:

```shell
shell> ./configure --help
```

Examples on how to enable support for (1) MySQL, (2) PostgreSQL and (3) SQLite:

1. libmysqlclient-dev package or (self-compiled) equivalent being installed:
   
   ```shell
   shell> ./configure --enable-mysql
   ```
 
1. libpq-dev package or (self-compiled) equivalent being installed:
   
   ```shell
   shell> ./configure --enable-pgsql
   ```
 
1. libsqlite3-dev package or (self-compiled) equivalent being installed:
   
   ```shell
   shell> ./configure --enable-sqlite3
   ```

If cloning the GitHub repository ( https://github.com/pmacct/pmacct ) instead,
the configure script has to be generated, resulting in one extra step than the
process just described. Please refer to the Building section of the README.md
document for instruction about cloning the repo, generate the configure script
along with the required installed packages.

Then compile and install simply typing:

```shell
shell> make; make install
```

Should you want, for example, to compile pmacct with PostgreSQL support and
have installed PostgreSQL in /usr/local/postgresql and pkg-config is unable
to help, you can supply this non-default location as follows (assuming you
are running the bash shell):

```shell
shell> export PGSQL_LIBS="-L/usr/local/postgresql/lib -lpq"
shell> export PGSQL_CFLAGS="-I/usr/local/postgresql/include"
shell> ./configure --enable-pgsql
```

If the library does actually support pkg-config but the .pc pkg-config file
is in some non-standard location, this can be supplied as follows:

```shell
shell> export PKG_CONFIG_PATH=/usr/local/postgresql/pkgconfig/
shell> ./configure --enable-pgsql
```

Special case is to compile pmacct with MySQL support but MySQL is installed
in some non-default location. MySQL brings the mysql_config tool that works
similarly to pkg-config. Make sure the tool is on the path so that it can be
executed by the configure script, ie.:

```shell
shell> export PATH=$PATH:/usr/local/mysql/bin
shell> ./configure --enable-mysql
```

By default all tools - flow, BGP, BMP and Streaming Telemetry - are compiled.
Specific tool sets can be disabled. For example, to compile only flow tools
(ie. no pmbgpd, pmbmpd, pmtelemetryd) the following command-line can be used:

```shell
shell> ./configure --disable-bgp-bins --disable-bmp-bins --disable-st-bins
```

Once daemons are installed you can check:

* Basic instrumenting of each daemon via its help page, ie.: 
  
  ```
  shell> pmacctd -h
  ```
* Review daemon version and build details, ie.:
  
  ```shell
  shell> sfacctd -V
  ```
* Check supported traffic aggregation primitives and their description, ie.:
  
  ```
  shell> nfacctd -a
  ```

## IIa. Compiling pmacct with JSON support

JSON encoding is supported via the Jansson library (http://www.digip.org/jansson/
and https://github.com/akheron/jansson); a library version >= 2.5 is required. To
compile pmacct with JSON support simply do: 

```shell
shell> ./configure --enable-jansson
```

However should you have installed Jansson in the /usr/local/jansson directory
and pkg-config is unable to help, you can supply this non-default location as
follows (assuming you are running the bash shell):

```shell
shell> export JANSSON_LIBS="-L/usr/local/jansson/lib -ljansson"
shell> export JANSSON_CFLAGS="-I/usr/local/jansson/include"
shell> ./configure --enable-jansson
```

## IIb. Compiling pmacct with Apache Avro support

Apache Avro encoding is supported via libavro library (http://avro.apache.org/
and https://avro.apache.org/docs/1.9.1/api/c/index.html); Avro depends on the
Jansson JSON parser version 2.3 or higher so please review the previous section
"Compiling pmacct with JSON support"; then, to compile pmacct with Apache Avro
support simply do:

```shell
shell> ./configure --enable-jansson --enable-avro
```

However should you have installed libavro in the /usr/local/avro directory
and pkg-config is unable to help, you can supply this non-default location as
follows (assuming you are running the bash shell):

```shell
shell> export AVRO_LIBS="-L/usr/local/avro/lib -lavro"
shell> export AVRO_CFLAGS="-I/usr/local/avro/include"
shell> ./configure --enable-kafka --enable-jansson --enable-avro
```

## IIc. Compiling pmacct against a own libpcap library

Compiling against a downloaded libpcap library may be wanted for several
reasons including the version packaged with the Operating System is too
old, a custom libpcap library needs to be compiled (ie. with support for
PF_RING) or static linking is wanted.

Once libpcap is downloaded, if static linking is wanted (ideal for example
for distributing pmacct without external dependencies), the library can be
configured for comipiling:

```shell
shell> ./configure --disable-so
```

Which passes the compiler the '-static' knob. pmacct should be pointed to
the own libpcap library when configuring for compiling:

```shell
shell> ./configure --with-pcap-libs=/path/to/libpcap-x.y.z --with-pcap-includes=/path/to/libpcap-x.y.z
```

Once pmacct is compiled, it can be confirmed that the right library was
picked by doing, for example, a 'pmacctd -V' and seeing the version of
libpcap matches with the supplied version. It has to be noted however
that static compiling on GNU systems can yeld variable success; the
recommendation is to consider containers first (look into the 'docker/'
directory). 

A use-case for a PF_RING-enabled libpcap is that by hashing and balancing
collected traffic over multiple NIC queues (ie. if using Intel X520) it
is possible to scale pmacctd horizontally, with one pmacctd instance
reading from one or multiple queues. The queues can be managed via the
'ethtool' tool (ie. 'ethtool -l enp1s0f0' to list, 'ethtool -L enp1s0f0
combined 16' to access 16 queues, etc.) and pmacctd can be bound to a
single queue, ie. 'pmacctd -i enp1s0f0@0', or multiple ones via a
pcap_interfaces_map, ie.

```
ifname=enp1s0f0@0 ifindex=100
ifname=enp1s0f0@1 ifindex=101
ifname=enp1s0f0@2 ifindex=102
ifname=enp1s0f0@3 ifindex=103
```

# III. Brief SQL and noSQL setup examples
RDBMS require a table schema to store data. pmacct offers two options: use one
of the few pre-determined table schemas available (sections IIIa, b and c) or
compose a custom schema to fit your needs (section IIId). If you are blind to
SQL the former approach is recommended, although it can pose scalability issues
in larger deployments; if you know some SQL the latter is definitely the way to
go. Scripts for setting up RDBMS are located in the 'sql/' tree of the pmacct
distribution tarball. For further guidance read the relevant README files in
such directory. One of the crucial concepts to deal with, when using default
table schemas, is table versioning: please read more about this topic in the
FAQS document (Q17). 

## IIIa. MySQL examples 

```shell
shell> cd sql/
```

- To create v1 tables:

```shell
shell> mysql -u root -p < pmacct-create-db_v1.mysql
shell> mysql -u root -p < pmacct-grant-db.mysql
```

Data will be available in 'acct' table of 'pmacct' DB.

- To create v2 tables:

```shell
shell> mysql -u root -p < pmacct-create-db_v2.mysql
shell> mysql -u root -p < pmacct-grant-db.mysql
```

Data will be available in 'acct_v2' table of 'pmacct' DB.

... And so on for the newer versions.

## IIIb. PostgreSQL examples
Which user has to execute the following two scripts and how to autenticate with the
PostgreSQL server depends upon your current configuration. Keep in mind that both
scripts need postgres superuser permissions to execute some commands successfully:

```shell
shell> cp -p *.pgsql /tmp
shell> su - postgres
```

To create v1 tables:

```shell
shell> psql -d template1 -f /tmp/pmacct-create-db.pgsql
shell> psql -d pmacct -f /tmp/pmacct-create-table_v1.pgsql
```

To create v2 tables:

```shell
shell> psql -d template1 -f /tmp/pmacct-create-db.pgsql
shell> psql -d pmacct -f /tmp/pmacct-create-table_v2.pgsql
```

... And so on for the newer versions.

A few tables will be created into 'pmacct' DB. 'acct' ('acct_v2' or 'acct_v3') table is
the default table where data will be written when in 'typed' mode (see 'sql_data' option
in CONFIG-KEYS document; default value is 'typed'); 'acct_uni' ('acct_uni_v2' or
'acct_uni_v3') is the default table where data will be written when in 'unified' mode.

Since v6, PostgreSQL tables are greatly simplified: unified mode is no longer supported
and an unique table ('acct_v6', for example) is created instead. 


## IIIc. SQLite examples

```shell
shell> cd sql/
```

- To create v1 tables:

```shell
shell> sqlite3 /tmp/pmacct.db < pmacct-create-table.sqlite3 
```

Data will be available in 'acct' table of '/tmp/pmacct.db' DB. Of course, you can change
the database filename basing on your preferences.  

- To create v2 tables:

```shell
shell> sqlite3 /tmp/pmacct.db < pmacct-create-table_v2.sqlite3 
```

Data will be available in 'acct_v2' table of '/tmp/pmacct.db' DB.

... And so on for the newer versions.


## IIId. Custom SQL tables

Custom tables can be built by creating your own SQL schema and indexes. This
allows to mix-and-match the primitives relevant to your accounting scenario.
To flag intention to build a custom table the sql_optimize_clauses directive
must be set to true, ie.:

sql_optimize_clauses: true
sql_table: <table name>
aggregate: <aggregation primitives list> 

How to build the custom schema? Let's say the aggregation method of choice
(aggregate directive) is "vlan, in_iface, out_iface, etype" the table name is
"acct" and the database of choice is MySQL. The SQL schema is composed of four
main parts, explained below:

1) A fixed skeleton needed by pmacct logics:

```sql
CREATE TABLE <table_name> (
	packets INT UNSIGNED NOT NULL,
	bytes BIGINT UNSIGNED NOT NULL,
	stamp_inserted DATETIME NOT NULL,
	stamp_updated DATETIME
);
```

2) Indexing: primary key (of your choice, this is only an example) plus
   any additional index you may find relevant.

3) Primitives enabled in pmacct, in this specific example the ones below; should
   one need more/others, these can be looked up in the *sql/README.mysql* file in
   the section named "Aggregation primitives to SQL schema mapping":

```sql
	vlan INT(2) UNSIGNED NOT NULL,
	iface_in INT(4) UNSIGNED NOT NULL,
	iface_out INT(4) UNSIGNED NOT NULL,
	etype INT(2) UNSIGNED NOT NULL,
```

4) Any additional fields, ignored by pmacct, that can be of use, these can be
   for lookup purposes, auto-increment, etc. and can be of course also part of
   the indexing you might choose. 

Putting the pieces together, the resulting SQL schema is below along with the
required statements to create the database:

```sql
DROP DATABASE IF EXISTS pmacct;
CREATE DATABASE pmacct;

USE pmacct;

DROP TABLE IF EXISTS acct;
CREATE TABLE acct (
	vlan INT(2) UNSIGNED NOT NULL,
	iface_in INT(4) UNSIGNED NOT NULL,
	iface_out INT(4) UNSIGNED NOT NULL,
	etype INT(2) UNSIGNED NOT NULL,
	packets INT UNSIGNED NOT NULL,
	bytes BIGINT UNSIGNED NOT NULL,
	stamp_inserted DATETIME NOT NULL,
	stamp_updated DATETIME,
	PRIMARY KEY (vlan, iface_in, iface_out, etype, stamp_inserted)
); 
```

To grant default pmacct user permission to write into the database look at the
file sql/pmacct-grant-db.mysql

## IIIe. Historical accounting

Enabling historical accounting allows to aggregate data in time-bins (ie. 5 mins, hour,
day, etc.) in a flexible and fully configurable way. Two timestamps are available: the
'stamp_inserted' field, representing the basetime of the time-bin, and 'stamp_updated',
the last time the time-bin was updated. Following a pretty standard config fragment to
slice data into nicely aligned (or rounded-off) 5 minutes time-bins:

```
sql_history: 5m 
sql_history_roundoff: m
```

## IIIf. INSERTs-only 

UPDATE queries are expensive; this is why, even if they are supported by pmacct, a
savy approach would be to cache data for longer times in memory and write them off
once per time-bin (sql_history): this results into a much lighter INSERTs-only setup.
This is an example based on 5 minutes time-bins:

```
sql_refresh_time: 300
sql_history: 5m
sql_history_roundoff: m
sql_dont_try_update: true
```

Note that sql_refresh_time is always expressed in seconds. An alternative approach
for cases where sql_refresh_time must be kept shorter than sql_history (for example
because a) of long sql_history periods, ie. hours or days, and/or because b) near
real-time data feed is a requirement) is to set up a synthetic auto-increment 'id'
field: it successfully prevents duplicates but comes at the expenses of GROUP BYs
when querying data.


# IV. Running the libpcap-based daemon (pmacctd) 
All deamons including pmacctd can be run with commandline options, using a
config file or a mix of the two. Sample configuration files are in examples/
tree. Note also  that most of the new features are available only as config
directives. To be aware of the existing configuration directives, please
read the CONFIG-KEYS document. 

Show all available pmacctd commandline switches:

```shell
shell> pmacctd -h
```

Run pmacctd reading configuration from a specified file (see examples/ tree
for a brief list of some commonly useed keys; divert your eyes to CONFIG-KEYS
for the full list). This example applies to all daemons:

```shell
shell> pmacctd -f pmacctd.conf
```

Daemonize the process; listen on eth0; aggregate data by src_host/dst_host;
write to a MySQL server; filter in only traffic with source prefix 10.0.0.0/16;
note that filters work the same as tcpdump so you can refer to libpcap/tcpdump
man pages for examples and further reading about the supported filtering syntax. 

```shell
shell> pmacctd -D -c src_host,dst_host -i eth0 -P mysql src net 10.0.0.0/16
```

Or written the configuration way:

```
!
daemonize: true
plugins: mysql
aggregate: src_host, dst_host
pcap_interface: eth0
pcap_filter: src net 10.0.0.0/16
! ...
```

Print collected traffic data aggregated by src_host/dst_host over the screen;
refresh data every 30 seconds and listen on eth0. 

```shell
shell> pmacctd -P print -r 30 -i eth0 -c src_host,dst_host
```

Or written the configuration way:

```
!
plugins: print
print_refresh_time: 30
aggregate: src_host, dst_host
pcap_interface: eth0
! ...
```

Print collected traffic data aggregated by src_host/dst_host over the screen;
refresh data every 30 seconds and listen on eth0 and eth1, listed in the file
pointed by pcap_interfaces_map (see 'examples/pcap_interfaces.map.example' for
more advanced uses of the map):

```
!
plugins: print
print_refresh_time: 30
aggregate: src_host, dst_host
pcap_interfaces_map: /path/to/pcap_interfaces.map
! ...
```

Then in */path/to/pcap_interfaces.map*:

```
!
ifindex=100	ifname=eth0
ifindex=200	ifname=eth1
! ...
```

Daemonize the process; let pmacct aggregate traffic in order to show in vs out
traffic for network 192.168.0.0/16; send data to a PostgreSQL server. This
configuration is not possible via commandline switches; the corresponding
configuration follows: 

```
! 
daemonize: true
plugins: pgsql[in], pgsql[out]
aggregate[in]: dst_host
aggregate[out]: src_host
aggregate_filter[in]: dst net 192.168.0.0/16
aggregate_filter[out]: src net 192.168.0.0/16
sql_table[in]: acct_in
sql_table[out]: acct_out
! ...
```

And now enabling historical accounting. Split traffic by hour and write
to the database every 60 seconds:

```
!
daemonize: true
plugins: pgsql[in], pgsql[out]
aggregate[in]: dst_host
aggregate[out]: src_host
aggregate_filter[in]: dst net 192.168.0.0/16
aggregate_filter[out]: src net 192.168.0.0/16
sql_table[in]: acct_in
sql_table[out]: acct_out
sql_refresh_time: 60
sql_history: 1h
sql_history_roundoff: h
! ...
```

Let's now translate the same example in the memory plugin world. One of
the use-cases for this plugin is when feeding 3rd party tools with bytes/
packets/flows counters. Examples how to query the memory table with the
'pmacct' client tool will follow later in this document. Now, note that
each memory table need its own pipe file in order to get queried by the
client:

```
!
daemonize: true
plugins: memory[in], memory[out]
aggregate[in]: dst_host
aggregate[out]: src_host
aggregate_filter[in]: dst net 192.168.0.0/16
aggregate_filter[out]: src net 192.168.0.0/16
imt_path[in]: /tmp/pmacct_in.pipe
imt_path[out]: /tmp/pmacct_out.pipe
! ...
```

As a further note, check CONFIG-KEYS document about more imt_* directives
as they will support in the task of fine tuning the size and boundaries
of memory tables, if default values are not ok for your setup. 

Now, fire multiple instances of pmacctd, each on a different interface;
again, because each instance will have its own memory table, it will
require its own pipe file for client queries aswell (as explained in the
previous examples):

```shell
shell> pmacctd -D -i eth0 -m 8 -s 65535 -p /tmp/pipe.eth0 
shell> pmacctd -D -i ppp0 -m 0 -s 32768 -p /tmp/pipe.ppp0 
```

Run pmacctd logging what happens to syslog and using "local2" facility:

```shell
shell> pmacctd -c src_host,dst_host -S local2
```

NOTE: superuser privileges are needed to execute pmacctd correctly. 


# V. Running the NetFlow/IPFIX and sFlow daemons (nfacctd/sfacctd) 

All examples about pmacctd are also valid for nfacctd and sfacctd with the exception
of directives that apply exclusively to libpcap. If you have skipped examples in the
previous section, please read them before continuing. All config keys available are
in the CONFIG-KEYS document. Some examples:

Run nfacctd reading configuration from a specified file:

```shell
shell> nfacctd -f nfacctd.conf
```

Daemonize the process; aggregate data by sum_host (by host, summing inbound + outbound
traffic); write to a local MySQL server. Listen on port 5678 for incoming Netflow
datagrams (from one or multiple NetFlow agents):

```shell
shell> nfacctd -D -c sum_host -P mysql -l 5678 
```

Let's now configure pmacct to insert data in MySQL every two minutes, enable historical
accounting with 10 minutes time-bins and make use of a SQL table version 4:

```
!
daemonize: true
plugins: mysql
aggregate: sum_host
nfacctd_port: 5678
sql_refresh_time: 120
sql_history: 10m
sql_history_roundoff: mh
sql_table_version: 4
! ...
```

## Va. NetFlow daemon & accounting NetFlow v9/IPFIX options 
NetFlow v9/IPFIX can send option records other than flow ones, typically used to send
to a collector mappings among interface SNMP ifIndexes to interface names or VRF ID's
to VRF names or extra sampling information. nfacctd_account_options enables accounting
of option records then these should be split from regular flow records. Below is a
sample config:

```
nfacctd_time_new: true
nfacctd_account_options: true
!
plugins: print[data], print[option_vrf], print[option_if], print[option_sampling]
!
pre_tag_filter[data]: 100
aggregate[data]: peer_src_ip, in_iface, out_iface, tos, vrf_id_ingress, vrf_id_egress
print_refresh_time[data]: 300
print_history[data]: 300
print_history_roundoff[data]: m
print_output_file_append[data]: true
print_output_file[data]: /path/to/flow_%s
print_output[data]: csv
!
pre_tag_filter[option_vrf]: 200
aggregate[option_vrf]: peer_src_ip, vrf_id_ingress, vrf_name
print_refresh_time[option_vrf]: 300
print_history[option_vrf]: 300
print_history_roundoff[option_vrf]: m
print_output_file_append[option_vrf]: true
print_output_file[option_vrf]: /path/to/option_vrf_%s
print_output[option_vrf]: event_csv
!
pre_tag_filter[option_if]: 200
aggregate[option_if]: peer_src_ip, in_iface, int_descr
print_refresh_time[option_if]: 300
print_history[option_if]: 300
print_history_roundoff[option_if]: m 
print_output_file_append[option_if]: true
print_output_file[option_if]: /path/to/option_if_%s
print_output[option_if]: event_csv
!
pre_tag_filter[option_sampling]: 200
aggregate[option_sampling]: peer_src_ip, sampler_id, sampler_interval 
print_refresh_time[option_sampling]: 300
print_history[option_sampling]: 300
print_history_roundoff[option_sampling]: m 
print_output_file_append[option_sampling]: true
print_output_file[option_sampling]: /path/to/option_sampling_%s
print_output[option_sampling]: event_csv
!
aggregate_primitives: /path/to/primitives.lst
pre_tag_map: /path/to/pretag.map
maps_refresh: true
```

Below is the referenced pretag.map:

```
set_tag=100     ip=0.0.0.0/0    sample_type=flow
set_tag=200     ip=0.0.0.0/0    sample_type=option
```

Below is the referenced primitives.lst:

```
name=vrf_id_ingress     field_type=234  len=4   semantics=u_int
name=vrf_id_egress      field_type=235  len=4   semantics=u_int
name=vrf_name           field_type=236  len=32  semantics=str
!
name=int_descr		field_type=83	len=64	semantics=str
!
name=sampler_interval	field_type=50	len=4	semantics=u_int
name=sampler_id		field_type=48	len=2	semantics=u_int
```

## Vb. Distributing NetFlow v9/IPFIX templates when clustering
One of the possible ways to cluster multiple nfacctd daemons running on the same
system (ie. to harness all [configured] CPU threads) is to rely on the Linux/BSD
SO_REUSEPORT feature (read more in the "Miscellaneous notes and troubleshooting
tips" section of this document).

NetFlow v9/IPFIX protocols are template-based and templates are emitted in
specific Options packets and are indeed needed in order to properly decode
actual Data packets. Hence a load-balancing cluster (when not hashing but
performing some sort of round-robin) does pose the problem of disseminating the
templates across the clustered daemons. For this very purpose there are two
config knobs: nfacctd_templates_receiver (to export received templates) and
nfacctd_templates_port (to define a port to receive templates from the rest
of the cluster). When multiple daemons are clustered a replicator (nfacctd with
'tee' plugin configured is required). Here is an example of the configs needed:

nfacctd clustered daemon config (other daemons in the same cluster would be
listening on different nfacctd_templates_port ports, ie. 20002, 20003, etc.):

```
!
! [ .. existing config .. ]
!
nfacctd_templates_receiver: 127.0.0.1:10000
nfacctd_templates_port: 20001
```

The replicator piece needs two bits, a config and a tee_receivers file (in the
example receivers.lst). Here is the config:

```
nfacctd_port: 10000
!
plugins: tee[a]
!
tee_receivers[a]: /path/to/receivers.lst
tee_transparent[a]: true 
```

And here is the receivers.lst file:

```
id=1   ip=127.0.0.1:20001,127.0.0.1:20002,127.0.0.1:20003,[..]
```

## Vc. Examples configuring NetFlow v9/IPFIX export

Example to configure NetFlow v9 export on a Cisco running IOS/IOS-XE:

```
ip flow-cache timeout active 1
ip flow-cache mpls label-positions 1
!
ip flow-export source Loopback0
ip flow-export version 9 bgp-nexthop
ip flow-export template timeout-rate 1
ip flow-export template refresh-rate 4
ip flow-export destination X.X.X.X 2100
!
interface GigabitEthernet0/0
 ip address Y.Y.Y.Y Z.Z.Z.Z
 ip flow ingress
```

Example to configure NetFlow v9 export on a Cisco running IOS-XR:

```
sampler-map NFACCTD-SMP
 random 1 out-of 10
!
flow monitor-map NFACCTD-MON
 record ipv4
 exporter NFACCTD-EXP
!
flow exporter-map NFACCTD-EXP
 version v9 
 transport udp 2100
 destination X.X.X.X
!
interface GigabitEthernet0/0/0/1
 ipv4 address Y.Y.Y.Y Z.Z.Z.Z
 flow ipv4 monitor NFACCTD-MON sampler NFACCTD-SMP ingress
```

Example to configure IPFIX export on a Juniper:

```
services {
  flow-monitoring {
    version-ipfix {
      template ipv4 {
	flow-active-timeout 60;
	flow-inactive-timeout 70;
	template-refresh-rate seconds 30;
	option-refresh-rate seconds 30;
	ipv4-template;
      }
    }
  }
}

chassis {
  fpc 0 {
    sampling-instance s1;
  }
}

forwarding-options {
  sampling {
    instance {
      s1 {
	input {
	  rate 10;
	}
	family inet {
	  output {
	    flow-server X.X.X.X {
	      port 2100;
	      version-ipfix {
		template {
		  ipv4;
		}
	      }
	    }
	    inline-jflow {
	      source-address Y.Y.Y.Y;
	    }
	  }
	}
      }
    }
  }
}
```

Example to configure NetFlow v9 export on a Huawei:

```
ip netstream timeout active 1
ip netstream timeout inactive 5
ip netstream mpls-aware label-and-ip
ip netstream export version 9 origin-as bgp-nexthop
ip netstream export index-switch 32
ip netstream export template timeout-rate 1
ip netstream sampler fix-packets 1000 inbound
ip netstream export source Y.Y.Y.Y
ip netstream export host X.X.X.X 2100

ipv6 netstream timeout active 1
ipv6 netstream timeout inactive 5
ipv6 netstream mpls-aware label-and-ip
ipv6 netstream export version 9 origin-as bgp-nexthop
ipv6 netstream export index-switch 32
ipv6 netstream export template timeout-rate 1
ipv6 netstream sampler fix-packets 1000 inbound

interface Eth-Trunk1.100
  ip netstream inbound
  ipv6 netstream inbound
```

Contribution of further configuration examples for Cisco and Juniper devices
and/or other relevant vendors is more than welcome.


# VI. Running the NFLOG-based daemon (uacctd)

All examples about pmacctd are also valid for uacctd with the exception of directives
that apply exclusively to libpcap. If you've skipped examples in the "Running the
libpcap-based daemon (pmacctd)" section, please read them before continuing. All
configuration keys available are in the CONFIG-KEYS document.

The daemon depends on the package libnetfilter-log-dev in Debian/Ubuntu,
libnetfilter_log in CentOS/RHEL (or equivalent package in the preferred Linux
distribution). The support for NFLOG is disabled by default and should be enabled
as follows:

```shell
shell> ./configure --enable-nflog
```

NFLOG_CFLAGS and NFLOG_LIBS can be used if includes and library are not in default
locations. The Linux NFLOG infrastructure requires a couple parameters in order to
work properly: the NFLOG multicast group (uacctd_group) to which captured packets
have to be sent to and the Netlink buffer size (uacctd_nl_size). The default buffer
settings (128KB) typically works OK for small environments. The traffic is captured
with an iptables rule. For example in one of the following ways:

```shell
* iptables -t mangle -I POSTROUTING -j NFLOG --nflog-group 5
* iptables -t raw -I PREROUTING -j NFLOG --nflog-group 5 
```

Apart from determining how and what traffic to capture with iptables, which is topic
outside the scope of this document, the most relevant point is the "--nflog-nlgroup"
iptables setting has to match with the "uacctd_group" uacctd one. To review the packet
flow in iptables: https://commons.wikimedia.org/wiki/File:Netfilter-packet-flow.svg

A couple examples follow:

Run uacctd reading configuration from a specified file.

```shell
shell> uacctd -f uacctd.conf
```

Daemonize the process; aggregate data by sum_host (by host, summing inbound + outbound
traffic); write to a local MySQL server. Listen on NFLOG multicast group #5. Let's make
pmacct divide data into historical time-bins of 5 minutes. Let's disable UPDATE queries
and hence align refresh time with the timeslot length. Finally, let's make use of a SQL
table, version 4:

```
!
uacctd_group: 5
daemonize: true
plugins: mysql
aggregate: sum_host
sql_refresh_time: 300
sql_history: 5m
sql_history_roundoff: mh
sql_table_version: 4
sql_dont_try_update: true
! ...
```

# VII. Running the pmacct IMT client (pmacct)
The 'pmacct' client tool allows to query memory tables. Messaging happens over a UNIX
pipe file: authorization is strictly connected to permissions of the pipe file. Note:
while writing queries commandline, it may happen to write chars with a special meaning
for the shell itself (ie. ; or *). Mind to either escape ( \; or \* ) them or put in
quotes ( " ).

Show all available pmacct client commandline switches:

```shell
shell> pmacct -h
```

Fetch data stored in the memory table:

```shell
shell> pmacct -s 
```

Fetch data stored in the memory table using JSON output (and nicely format it with
the 'jq' tool):

```shell
shell> pmacct -s -O json | jq 
```

Match data between source IP 192.168.0.10 and destination IP 192.168.0.3 and return
a formatted output; display all fields (-a), this way the output is easy to be parsed
by tools like awk/sed; each unused field will be zero-filled: 

```shell
shell> pmacct -c src_host,dst_host -M 192.168.0.10,192.168.0.3 -a
```

Similar to the previous example; it is requested to reset data for matched entries;
the server will return the actual counters to the client, then will reset them:

```shell
shell> pmacct -c src_host,dst_host -M 192.168.0.10,192.168.0.3 -r
```

Fetch data for IP address dst_host 10.0.1.200; we also ask for a 'counter only' output
('-N') suitable, this time, for injecting data in tools like MRTG or RRDtool (sample
scripts are in the examples/ tree). Bytes counter will be returned (but the '-n' switch
allows also select which counter to display). If multiple entries match the request (ie
because the query is based on dst_host but the daemon is actually aggregating traffic
as "src_host, dst_host") their counters will be summed:

```shell
shell> pmacct -c dst_host -N 10.0.1.200
```

Query the memory table available via pipe file /tmp/pipe.eth0:

```shell
shell> pmacct -c sum_port -N 80 -p /tmp/pipe.eth0 
```

Find all data matching host 192.168.84.133 as either their source or destination address.
In particular, this example shows how to use wildcards and how to spawn multiple queries
(each separated by the ';' symbol). Take care to follow the same order when specifying
the primitive name (-c) and its actual value ('-M' or '-N'):

```shell
shell> pmacct -c src_host,dst_host -N "192.168.84.133,*;*,192.168.84.133"
```

Find all web and smtp traffic; we are interested in have just the total of such traffic
(for example, to split legal network usage from the total); the output will be a unique
counter, sum of the partial (coming from each query) values.

```shell
shell> pmacct -c src_port,dst_port -N "25,*;*,25;80,*;*,80" -S 
```

Show traffic between the specified hosts; this aims to be a simple example of a batch
query; note that as value of both '-N' and '-M' switches it can be supplied a value like:
'file:/home/paolo/queries.list': actual values will be read from the specified file (and
they need to be written into it, one per line) instead of commandline:

```shell
shell> pmacct -c src_host,dst_host -N "10.0.0.10,10.0.0.1;10.0.0.9,10.0.0.1;10.0.0.8,10.0.0.1"
shell> pmacct -c src_host,dst_host -N "file:/home/paolo/queries.list"
```

# VIII. Running the RabbitMQ/AMQP plugin
The Advanced Message Queuing Protocol (AMQP) is an open standard for passing business
messages between applications. RabbitMQ is a messaging broker, an intermediary for
messaging, which implementes AMQP. pmacct RabbitMQ/AMQP plugin is designed to send
aggregated network traffic data, in JSON or Avro format, through a RabbitMQ server
to 3rd party applications (typically, but not limited to, noSQL databases like
ElasticSearch, InfluxDB, etc.). Requirements to use the plugin are:

* A working RabbitMQ server: http://www.rabbitmq.com/
* RabbitMQ C API, rabbitmq-c: https://github.com/alanxz/rabbitmq-c/
* Libjansson to cook JSON objects: http://www.digip.org/jansson/

Additionally, the Apache Avro C library (http://avro.apache.org/) needs to be
installed to be able to send messages packed using Avro (you will also need to
pass --enable-avro to the configuration script).

Once these elements are installed, pmacct can be configured for compiling. pmacct
makes use of pkg-config for finding libraries and headers location and checks some
"typical" default locations, ie. /usr/local/lib and /usr/local/include. So all
you should do is just:

```shell
shell> ./configure --enable-rabbitmq --enable-jansson
```

But, for example, should you have installed RabbitMQ in /usr/local/rabbitmq and
pkg-config is unable to help, you can supply this non-default location as follows 
(assuming you are running the bash shell):

```shell
shell> export RABBITMQ_LIBS="-L/usr/local/rabbitmq/lib -lrabbitmq" 
shell> export RABBITMQ_CFLAGS="-I/usr/local/rabbitmq/include"
shell> ./configure --enable-rabbitmq --enable-jansson
```

You can check further information on how to compile pmacct with JSON/libjansson
support in the section "Compiling pmacct with JSON support" of this document.

You can check further information on how to compile pmacct with Avro support in
the section "Compiling pmacct with Apache Avro support" of this document.

Then "make; make install" as usual. Following a configuration snippet showing a
basic RabbitMQ/AMQP plugin configuration (assumes: RabbitMQ server is available
at localhost; look all configurable directives up in the CONFIG-KEYS document):

```shell
! ..
plugins: amqp
!
aggregate: src_host, dst_host, src_port, dst_port, proto, tos
amqp_output: json
amqp_exchange: pmacct
amqp_routing_key: acct
amqp_refresh_time: 300
amqp_history: 5m
amqp_history_roundoff: m
! ..
```

pmacct will only declare a message exchange and provide a routing key, ie. it
will not get involved with queues at all. A basic consumer script, in Python,
is provided as sample to: declare a queue, bind the queue to the exchange and
show consumed data on the screen or post to a REST API. The script is located
in the pmacct default distribution tarball in 'examples/amqp/amqp_receiver.py'
and requires the 'pika' Python module installed. Should this not be available,
installation instructions are available at the following page:

http://www.rabbitmq.com/tutorials/tutorial-one-python.html


# IX. Running the Kafka plugin
Apache Kafka is a distributed streaming platform. Its qualities being: fast,
scalable, durable and distributed by design. pmacct Kafka plugin is designed
to send aggregated network traffic data, in JSON or Avro format, through a
Kafka broker to 3rd party applications (typically, but not limited to, noSQL
databases like ElasticSearch, InfluxDB, etc.). Requirements to use the plugin
are:

* A working Kafka broker (and Zookeper server): http://kafka.apache.org/
* Librdkafka: https://github.com/edenhill/librdkafka/
* Libjansson to cook JSON objects: http://www.digip.org/jansson/

Additionally, the Apache Avro C library (http://avro.apache.org/) needs to be
installed to be able to send messages packed using Avro (you will also need to
pass --enable-avro to the configuration script).

Once these elements are installed, pmacct can be configured for compiling.
pmacct makes use of pkg-config for finding libraries and headers location and
checks some default locations, ie. /usr/local/lib and /usr/local/include. If
this is satisfactory, all you should do is just:

```shell
shell> ./configure --enable-kafka --enable-jansson
```

But, for example, should you have installed Kafka in /usr/local/kafka and pkg-
config is unable to help, you can supply this non-default location as follows
(assuming you are running the bash shell):

```
shell> export KAFKA_LIBS="-L/usr/local/kafka/lib -lrdkafka"
shell> export KAFKA_CFLAGS="-I/usr/local/kafka/include"
shell> ./configure --enable-kafka --enable-jansson
```

You can check further information on how to compile pmacct with JSON/libjansson
support in the section "Compiling pmacct with JSON support" of this document.
As a proof-of-concept once some data is produced in JSON format to a Kafka topic,
it can be consumed with the kafka-console-consumer tool, part of standard Kafka
distribution, as:

```shell
kafka-console-consumer --bootstrap-server <Kafka broker host> \
	--topic <topic>
```

You can check further information on how to compile pmacct with Avro support in
the section "Compiling pmacct with Apache Avro support" of this document. Also,
if using Confluent Platform, a Schema Registry component is included with it and
allows for seamless inter-change of Avro schemas among producers and consumers
of a Kafka broker; to make use of this, pmacct should be compiled with libserdes
support:

```shell
shell> ./configure --enable-kafka --enable-jansson --enable-avro --enable-serdes
```

For further info on Confluent Schema Registry and libserdes:

[https://docs.confluent.io/current/schema-registry/docs/index.html]()

[https://github.com/confluentinc/libserdes]()

NOTE: issues have been reported for certain cases when using libserdes on a
system with OpenSSL 1.0.x installed due to some interactions with libcurl.
Please upgrade to OpenSSL 1.1.x or greater. 

Then "make; make install" as usual. As a proof-of-concept, when the Schema
Registry is in use, once some data is produced in Avro format to a Kafka topic,
it can be consumed with the kafka-avro-console-consumer tool, part of standard
Confluent Platform distribution, as: 

```shell
kafka-avro-console-consumer --bootstrap-server <Kafka broker host> \
	--topic <topic> \
	--property schema.registry.url=<Schema registry URL> \
	--skip-message-on-error
```

Following a configuration snippet showing a basic Kafka plugin configuration
(assumes: Kafka broker is available at 127.0.0.1 on port 9092; look all kafka_*
configurable directives up in the CONFIG-KEYS document):

```shell
! ..
plugins: kafka
!
aggregate: src_host, dst_host, src_port, dst_port, proto, tos
kafka_output: json
kafka_topic: pmacct.acct
kafka_refresh_time: 300
kafka_history: 5m
kafka_history_roundoff: m
!
! [Optional] librdkafka config for buffer tuning, ssl config, etc. 
! kafka_config_file: /path/to/librdkafka.conf
!
! [Optional] Schema Registry URL
! kafka_avro_schema_registry: https://localhost
! ..
```

A basic script, in Python, is provided as sample to consume JSON/Avro data from
a given topic and perform some simple actions (ie. post data to a new Kafka topic,
post to a URL or print to screen). The script is located in the pmacct distribution
code in 'examples/kafka/kafka_consumer.py' and requires the confluent-kafka-python
Python module installed (among the others, check script header). Should this not
be available you can read on the following page how to get it installed:

[https://github.com/confluentinc/confluent-kafka-python]()

This is a pointer to the quick start guide to Kafka:

[https://kafka.apache.org/quickstart]()

Some notes:

1. When using Kafka over a dedicated node or VM, you may have to update the default Kafka server configuration. Edit the file named server.properties under the config folder of your kafka installation. Uncomment the following parameters:

    * listeners,
    * advertised.listeners,
    * listener.security.protocol.map

  and configure it according to your Kafka design. Taking a simple example where there is one single Kafka node used for both Zookeeper and Kafka and this node is using and ip address like 172.16.2.1. Those three parameters will look like this:

  ```
  listeners=PLAINTEXT://172.16.2.1:9092
  advertised.listeners=PLAINTEXT://172.16.2.1:9092
  listener.security.protocol.map=PLAINTEXT:PLAINTEXT,SSL:SSL,SASL_PLAINTEXT:SASL_PLAINTEXT,SASL_SSL:SASL_SSL
  ```

1. When the amount of data published to Kafka is substantial, ie. in the order of thousands of entries per second, batching (MessageSet) is needed in order to avoid every single object being produced singularly to Kafka brokers. Two strategies are available for this a) pmacct batching via the kafka_multi_values feature (legacy) or b) librdkafka batching (recommended) via, as per the lib documentation, "The two most important configuration properties for performance tuning [are]:

    * batch.num.messages : the minimum number of messages to wait for to accumulate in the local queue before sending off a message set.
    * queue.buffering.max.ms : how long to wait for batch.num.messages to fill up in the local queue.". Note: up until librdkafka 0.11, the default was kept very low to favour low-latency. A sensible minimum value in high-throughput scenarios is 50ms.

  Also, intuitively, queue.buffering.max.messages, the "Maximum number of messages allowed on the producer queue", should be kept greater than the batch.num.messages. These knobs can all be supplied to librdkafka through pmacct via a file pointed by kafka_config_file, as global settings, ie.:

  ``` 
  global, queue.buffering.max.messages, 8000000
  global, batch.num.messages, 100000
  global, queue.buffering.max.ms, 50
  ```

1. Configuring statistics.interval.ms to a positive value in kafka_config_file will make librdkafka log plenty of internal metrics - as documented at the following wiki page: [https://github.com/edenhill/librdkafka/wiki/Statistics]() . For example:
  
  ```
  global, statistics.interval.ms, 60000
  ```

1. SSL and SASL supports in librdkafka are totally configuration based, meaning they can be enabled via the kafka_config_file. More info is available at the pages: [https://github.com/edenhill/librdkafka/wiki/Using-SSL-with-librdkafka]() and [https://github.com/edenhill/librdkafka/wiki/Using-SASL-with-librdkafka]() . 

  For example, quoting the librdkafka page for SSL:

  ```
  global, security.protocol, ssl
  global, ssl.ca.location, ca-cert
  global, ssl.certificate.location, client_?????_client.pem
  global, ssl.key.location, client_?????_client.key
  global, ssl.key.password, abcdefgh
  ```

  Or, for example, trying to connect to Microsoft Azure via their Kafka API using SASL:

  ```
  global, security.protocol, SASL_SSL
  global, sasl.mechanism, PLAIN
  global, sasl.username, $ConnectionString
  global,sasl.password,Endpoint=sb://.XXX.windows.net/;SharedAccessKeyName=YYY;SharedAccessKey=ZZZ;EntityPath=JJJ
  ```

1. When integrating pmacct with the PNDA framework ( [http://www.pnda.io/]() ), a guide on how to make the two communicate has been written-up and published at
this URL: [https://github.com/jbotello7381/pmacct_to_pnda.io]() . 


1. Internal buffering and queueing
  Two options are provided for internal buffering and queueing: 
  1. a home-grown circular queue implementation available since day one of pmacct (configured via plugin_pipe_size and documented in docs/INTERNALS); and 
  2. a ZeroMQ queue (configured via plugin_pipe_zmq and plugin_pipe_zmq_* directives).

For a quick comparison: while relying on a ZeroMQ queue does introduce an external
dependency, ie. libzmq, it reduces the amount of trial and error needed to fine
tune plugin_buffer_size and plugin_pipe_size directives needed by the home-grown
queue implementation.

The home-grown cicular queue has no external dependencies and is configured, for
example, as:

```
plugins: print[blabla]
plugin_buffer_size[blabla]: 10240
plugin_pipe_size[blabla]: 1024000
```

For more information about the home-grown circular queue, consult plugin_buffer_size
and plugin_pipe_size entries in CONFIG-KEYS and docs/INTERNALS "Communications between
core process and plugins" chapter. 

ZeroMQ, from 0MQ The Guide, "looks like an embeddable networking library but acts like
a concurrency framework. It gives you sockets that carry atomic messages across various
transports like in-process, inter-process, TCP, and multicast. You can connect sockets
N-to-N with patterns like fan-out, pub-sub, task distribution, and request-reply. It's
fast enough to be the fabric for clustered products. Its asynchronous I/O model gives
you scalable multicore applications, built as asynchronous message-processing tasks.
[ .. ]". pmacct integrates ZeroMQ using a pub-sub queue architecture, using ephemeral
TCP ports and implementing plain authentication (username and password, auto-generated
at runtime).

The only requirement to use a ZeroMQ queue is to have the latest available stable
release of libzmq installed on the system (http://zeromq.org/intro:get-the-software ,
https://github.com/zeromq/libzmq/releases). Once this is installed, pmacct can be
configured for compiling. pmacct makes use of pkg-config for finding libraries and
headers location and checks some "typical" default locations, ie. /usr/local/lib and
/usr/local/include. So all you should do is just:

```shell
shell> ./configure --enable-zmq
```

But, for example, should you have installed ZeroMQ in /usr/local/zeromq and should also
pkg-config be unable to help, the non-default location can be supplied as follows (bash
shell assumed):

```shell
shell> export ZMQ_LIBS="-L/usr/local/zeromq/lib -lzmq"
shell> export ZMQ_CFLAGS="-I/usr/local/zeromq/include"
shell> ./configure --enable-zmq
```

Then "make; make install" as usual. Following a configuration snippet showing how easy
is to leverage ZeroMQ for queueing (see CONFIG-KEYS for all ZeroMQ-related options):

```shell
plugins: print[blabla]
plugin_pipe_zmq[blabla]: true 
plugin_pipe_zmq_profile[blabla]: micro
```

Please review the standard buffer profiles, plugin_pipe_zmq_profile, in CONFIG-KEYS;
Q21 of FAQS describes how to estimate the amount of flows/samples per second of your
deployment.


# XI. Quickstart guide to packet/flow classification
Packet classification is a feature available for pmacctd (libpcap-based daemon),
uacctd (NFLOG-based daemon), nfacctd (NetFlow daemon) via NetFlow v9/IPFIX IE #315
(dataLinkFrameSection) and sfacctd (sFlow daemon) via sFlow v5 raw header sample
and the current approach is to leverage the popular free, open-source nDPI library.
To enable the feature please follow these steps:

1. Download pmacct from its webpage ([http://www.pmacct.net/]()) or from its GitHub
   repository (https://github.com/pmacct/pmacct).

1. Download nDPI from its GitHub repository ([https://github.com/ntop/nDPI]()). The
   nDPI API tends to change frequently in a non-backward compatible fashion.
   This means that not every version of pmacct will work with any version of
   nDPI. pmacct 1.7.5 works against nDPI 3.0-stable, pmacct 1.7.6 works against
   nDPI 3.2-stable.  

1. Configure for compiling, compile and install the downloaded nDPI library, ie.
   inside the nDPI directory:
   
   ```shell
   shell> ./autogen.sh; ./configure; make; make install; ldconfig 
	```


1. Configure for compiling pmacct with the *--enable-ndpi* switch. Then compile and
   install, ie.:

   If downloading a release from [http://www.pmacct.net](), from inside the pmacct
   directory:
   
   ```shell
   shell> ./configure --enable-ndpi; make; make install
   ```
   
   If downloading code from [https://github.com/pmacct/pmacct]() , from inside the
   pmacct directory:
   
   ```shell
   shell> ./autogen.sh; ./configure --enable-ndpi; make; make install
	```

   If using a nDPI library that is not installed (or not installed in a default
   location) on the system, then NDPI_LIBS and NDPI_CFLAGS should be set to the
   location where nDPI headers and dynamic library are lyingi, for example:

	```shell
   shell> NDPI_LIBS=-L/path/to/nDPI/src/lib/.libs  
   shell> NDPI_CFLAGS=-I/path/to/nDPI/src/include
   shell> export NDPI_LIBS NDPI_CFLAGS
   shell> ./configure --enable-ndpi
   shell> make; make install
	```
	
   If using a nDPI library that does not install libndpi.pc pkg-config file in a
   standard directory, then PKG_CONFIG_PATH should be set (this seems to be true
   for both 2.6 and 2.8 releases), for example:

	```shell
   shell> PKG_CONFIG_PATH=/usr/local/libdata/pkgconfig
   shell> export PKG_CONFIG_PATH
   shell> ./configure --enable-ndpi
   shell> make; make install
	```
	
1. Configure pmacct. The following sample configuration is based on pmacctd and
   the print plugin with formatted output to stdout: 
	
	```shell
   daemonize: true
   pcap_interface: eth0
   snaplen: 700
   !
   plugins: print
   !
   aggregate: src_host, dst_host, src_port, dst_port, proto, tos, class
	```
	
   What enables packet classification is the use of the 'class' primitive as part
   of the supplied aggregation method. Further classification-related options, 
   such as timers, attempts, etc., are documented in the CONFIG-KEYS document
   (classifier_* directives). 

1. Execute pmacct as:

	```shell
   shell> pmacctd -f /path/to/pmacctd.conf
	```

Flow classification is a feature available for nfacctd (NetFlow daemon) and relies
on NetFlow v9/IPFIX IEs #94, #95 and #96. Where IE #95 (applicationId) is part of
flow data and can be looked up against Options data where IE #96 (applicationName) 
and IE #94 (applicationDescription) are supplied - specifically applicationName is
the one used for the 'class' primitive value. To enable the feature, if the NetFlow/
IPFIX exporter does follow NBAR implementation (and pmacct nfprobe plugin does!),
simply add the 'class' primitive to the existing 'aggregate' aggregation method.


# XII. Quickstart guide to setup a NetFlow/IPFIX agent/probe

pmacct is able to export traffic data through both NetFlow and sFlow protocols. This
section covers NetFlow/IPFIX and next one covers sFlow. While NetFlow v5 is fixed by
nature, v9 adds (to v5) flexibility allowing to transport custom information (ie.
classification information or custom tags to remote collectors) and IPFIX adds (to
v9) the chance to transport private information (PEN) and variable-length elements.
Below the configuration guide:

1. usual initial steps: download pmacct, unpack it, compile it.

1. build NetFlow probe configuration, using pmacctd:

	```
   !
   daemonize: true
   pcap_interface: eth0
   aggregate: src_host, dst_host, src_port, dst_port, proto, tos
   plugins: nfprobe
   nfprobe_receiver: 192.168.1.1:2100
   ! nfprobe_receiver: [FD00::2]:2100
   nfprobe_version: 10
   ! nfprobe_engine: 1:1
   ! nfprobe_timeouts: tcp=120:maxlife=3600
   !
   ! networks_file: /path/to/networks.lst
   !...
   ```

   This is a basic working configuration. Additional probe features include:

   1. generate ASNs by using a networks_file pointing to a valid Networks File (see
   examples/ directory) and adding src_as, dst_as primitives to the 'aggregate'
   directive; alternatively, it is possible to generate ASNs from the pmacctd BGP
   thread. The following fragment can be added to the config above:

   ```
   pmacctd_as: bgp
   bgp_daemon: true
   bgp_daemon_ip: 127.0.0.1
   bgp_agent_map: /path/to/bgp_agent.map
   bgp_daemon_port: 17917
   ```

   The *bgp_daemon_port* can be changed from the standard BGP port (179/TCP) in order to
   co-exist with other BGP routing software which might be running on the same host.
   Furthermore, they can safely peer each other by using 127.0.0.1 as bgp_daemon_ip. 

   NOTE: Bird Internet Routing Daemon seems to dislike peerings on the same IP address
   it is configured on, even though the remote peer listens on a different TCP port;
   if Bird listens on 127.0.0.1 then setting up a 127.0.0.2 address on the system and
   binding pmacctd to it allows the BGP session to come up fine in a 127.0.0.1 <->
   127.0.0.2 fashion.
 
   In pmacctd, bgp_agent_map does the trick of mapping 0.0.0.0 to the IP address of
   the BGP peer (ie. 127.0.0.1: 'bgp_ip=127.0.0.1 ip=0.0.0.0'); this setup, while
   generic, was tested working in conjunction with Quagga and BIRD.

   Following a relevant fragment of the Quagga configuration:
   
   
   ```
   router bgp Y 
    bgp router-id X.X.X.X
    neighbor 127.0.0.1 remote-as Y 
    neighbor 127.0.0.1 port 17917
    neighbor 127.0.0.1 update-source X.X.X.X
   !
   ```

   Following a relevant fragment of the BIRD configuration:

   ```
   protocol bgp pmacctd46 {
      description "pmacctd";
      local 127.0.0.1 as YYYYY;
      neighbor 127.0.0.2 port 179 as YYYYY;
      rr client;
      hold time 90;
      keepalive time 30;
      graceful restart;

      ipv4 {
         next hop self;
         import filter {
            reject;
         };

         export filter {
            accept;
         };
      };

      ipv6 {
         next hop address 127.0.0.1;

         import filter {
            reject;
         };

         export filter {
            accept;
         };
      };
   }
   ```

   NOTE: if configuring a BGP neighbor over localhost via Quagga CLI the following
   message is returned: "% Can not configure the local system as neighbor". This
   is not returned when configuring the neighborship directly in the bgpd config
   file.

   2. encode flow classification information in NetFlow v9 like Cisco does with its
   NBAR/NetFlow v9 integration. This can be done by introducing the 'class' primitive
   to the aforementioned 'aggregate' and add the extra configuration directive:

	```
   aggregate: class, src_host, dst_host, src_port, dst_port, proto, tos
   snaplen: 700
	```

   Further information on this topic can be found in the 'Quickstart guide to packet
   classification' section of this document.

   3) add direction (ingress, egress) awareness to measured IP traffic flows. Direction
   can be defined statically (in, out) or inferred dinamically (tag, tag2) via the use
   of the nfprobe_direction directive. Let's look at a dynamic example using tag2;
   first, add the following lines to the daemon configuration:

   ```
   nfprobe_direction[plugin_name]: tag2
   pre_tag_map: /path/to/pretag.map
	```

   then edit the tag map as follows. A return value of '1' means ingress while '2' is
   translated to egress. It is possible to define L2 and/or L3 addresses to recognize
   flow directions. The 'set_tag2' primitive (tag2) will be used to carry the return
   value:


	```
    set_tag2=1 filter='dst host XXX.XXX.XXX.XXX'
    set_tag2=2 filter='src host XXX.XXX.XXX.XXX'

    set_tag2=1 filter='ether src XX:XX:XX:XX:XX:XX'
    set_tag2=2 filter='ether dst XX:XX:XX:XX:XX:XX'
   ```

   Indeed in such a case, the 'set_tag' primitive (tag) can be leveraged to other uses
   (ie. filter sub-set of the traffic for flow export);

   4) add interface (input, output) awareness to measured IP traffic flows. Interfaces
   can be defined only in addition to direction. Interface can be either defined
   statically (<1-4294967295>) or inferred dynamically (tag, tag2) with the use of the
   nfprobe_ifindex directive. Let's look at a dynamic example using tag; first add the
   following lines to the daemon config:
   
   ```
   nfprobe_direction[plugin_name]: tag
   nfprobe_ifindex[plugin_name]: tag2
   pre_tag_map: /path/to/pretag.map 
   ```

   then edit the tag map as follows:

   ```
   set_tag=1 filter='dst net XXX.XXX.XXX.XXX/WW' jeq=eval_ifindexes
   set_tag=2 filter='src net XXX.XXX.XXX.XXX/WW' jeq=eval_ifindexes
   set_tag=1 filter='dst net YYY.YYY.YYY.YYY/ZZ' jeq=eval_ifindexes
   set_tag=2 filter='src net YYY.YYY.YYY.YYY/ZZ' jeq=eval_ifindexes
   set_tag=1 filter='ether src YY:YY:YY:YY:YY:YY' jeq=eval_ifindexes
   set_tag=2 filter='ether dst YY:YY:YY:YY:YY:YY' jeq=eval_ifindexes
   set_tag=999 filter='net 0.0.0.0/0'
   !
   set_tag2=100 filter='dst host XXX.XXX.XXX.XXX' label=eval_ifindexes
   set_tag2=100 filter='src host XXX.XXX.XXX.XXX'
   set_tag2=200 filter='dst host YYY.YYY.YYY.YYY'
   set_tag2=200 filter='src host YYY.YYY.YYY.YYY'
   set_tag2=200 filter='ether src YY:YY:YY:YY:YY:YY'
   set_tag2=200 filter='ether dst YY:YY:YY:YY:YY:YY'
   ```

   The set_tag=999 works as a catch all for undefined L2/L3 addresses so
   to prevent searching further in the map. In the example above direction
   is set first then, if found, interfaces are set, using the jeq/label
   pre_tag_map construct.

c) build NetFlow collector configuration, using nfacctd:

   ```
   !
   daemonize: true
   nfacctd_ip: 192.168.1.1
   nfacctd_port: 2100
   plugins: memory[display]
   aggregate[display]: src_host, dst_host, src_port, dst_port, proto
   ! aggregate[display]: class, src_host, dst_host, src_port, dst_port, proto
   ```

d) Ok, we are done ! Now fire both daemons:
   
   ```shell
   shell a> pmacctd -f /path/to/configuration/pmacctd-nfprobe.conf
   shell b> nfacctd -f /path/to/configuration/nfacctd-memory.conf
   ```

# XIII. Quickstart guide to setup a sFlow agent/probe

pmacct can export traffic data via sFlow; such protocol is different from NetFlow/
IPFIX: in short, it works by sampling individual packets (and exporting portions of
them) instead of caching uni-directional flows as it happens for NetFlow; such a 
statelss approach makes sFlow a light export protocol well-tailored for high-speed
networks. Furthermore, sFlow v5 can be extended much like NetFlow v9/IPFIX: meaning
classification information (if nDPI is compiled in, see 'Quickstart guide to packet
classification' section of this document), tags and/or basic Extended Gateway info
(ie. src_as, dst_as) can be easily included in the record structure being exported.
For classification info to be included in sFlow packets please make sure to specify
the classifier_num_roots directive in the config. Here a quickstarter sFlow probe
configuration, using pmacctd:

```
!
daemonize: true
pcap_interface: eth0
plugins: sfprobe
sampling_rate: 20
sfprobe_agentsubid: 1402
sfprobe_receiver: 192.168.1.1:6343
!
! sfprobe_agentip: FD00::1
! sfprobe_source_ip: FD00::1
! sfprobe_receiver: [FD00::2]:6343
!
! networks_file: /path/to/networks.lst
! snaplen: 700
!
! classifier_num_roots: 512
!
!...
```

# XIV. Quickstart guide to setup the BGP daemon

BGP can be run as a stand-alone collector daemon (pmbgpd) or as a thread within
one of the traffic accounting daemons (ie. nfacctd). The stand-alone daemon is
suitable for the Looking-Glass use-case, building BGP xconnects and consuming
BGP data, real-time or at regular intervals; the thread solution is suitable
for correlation of BGP with other data sources, ie. NetFlow, IPFIX, sFlow, etc.
The thread implementation idea is to receive data-plane information, ie. via
NetFlow, sFlow, etc., and control plane information, ie. full routing tables
via BGP, from edge routers. Per-peer BGP RIBs are maintained to ensure local
views of the network, a behaviour close to that of a BGP route-server. In case
of routers with default-only or partial BGP views, the default route can be
followed up (bgp_default_follow); also it might be desirable in certain
situations, for example trading-off resources to accuracy, to map one or a set
of flow agents to a BGP peer (bgp_agent_map). 

The following configuration snippet shows how to set up a BGP thread (ie. part
of the NetFlow/IPFIX collector, nfacctd) which will bind to an IP address and
will support up to a maximum number of 100 peers. Once PE routers start sending
flow telemetry data and peer up, it should be possible to see the BGP-related
fields, ie. as_path, peer_as_dst, local_pref, med, etc., correctly populated
while querying the memory table:

```
bgp_daemon: true
bgp_daemon_ip: X.X.X.X
bgp_daemon_max_peers: 100
! bgp_daemon_as: 65555
nfacctd_as: bgp
[ ... ]
plugins: memory
aggregate: src_as, dst_as, local_pref, med, as_path, peer_dst_as 
```

Setting up the stand-alone BGP collector daemon, pmbgpd, is not very different
at all from the configuration above:

```
bgp_daemon_ip: X.X.X.X
bgp_daemon_max_peers: 100
! bgp_daemon_as: 65555
bgp_table_dump_file: /path/to/spool/bgp-$peer_src_ip-%H%M.log
bgp_table_dump_refresh_time: 300
```

Essentially: the 'bgp_daemon: true' line is not required and there is no need
to instantiate plugins. On the other hand, the BGP daemon is instructed to dump
BGP tables to disk every 300 secs with file names embedding the BGP peer info
($peer_src_ip) and time reference (%H%M).

The BGP implementation, by default, reads the remote ASN upon receipt of a BGP
OPEN message and dynamically presents itself as part of the same ASN - this is
to ensure an iBGP relationship is established, even in multi ASN scenarios. It
is possible to put pmacct in a specific ASN of choice by using the bgp_daemon_as
configuration directive, for example, to establish an eBGP kind of relationship.
Also, the daemon acts as a passive BGP neighbor and hence will never try to
re-establish a fallen peering session. For debugging purposes related to the
BGP feed(s), bgp_daemon_msglog_* configuration directives can be enabled in
order to log BGP messaging.

NOTE: especially when connecting large amounts of BGP peers, say hundreds or
more, the almost synchronized attempt to connect from all of them may lead
the kernel into a suspicion of TCP SYN Flood. While not recommending to
disable TCP SYN flood protection, if slugginess is observed when taking up
the BGP sessions and kernel logs indicate a possible SYN flooding, maybe it
is good idea to tune and customize default kernel parameters.

XIVa. Limiting AS-PATH and BGP community attributes length
AS-PATH and BGP communities can get easily long when represented as strings.
Sometimes only a small portion of their content is of interest and hence a
simple filtering layer was developed in order to take special care of these
BGP attributes. bgp_aspath_radius cuts the AS-PATH down after a specified
amount of AS hops; whereas the bgp_stdcomm_pattern does a simple sub-string
matching against standard BGP communities, filtering in only those that match
(optionally, for better precision, a pre-defined number of characters can be
wildcarded by employing the '.' symbol, like in regular expressions). See an
example below:

```
bgp_aspath_radius: 3
bgp_stdcomm_pattern: 12345:
```

A detailed description of these configuration directives is, as usual, included in
the CONFIG-KEYS document. 

## XIVb. The source peer AS case 

The peer_src_as primitive adds useful insight in understanding where traffic enters
the observed routing domain; but asymmetric routing impacts accuracy delivered by
devices configured with either NetFlow or sFlow and the peer-as feature (as it only
performs a reverse lookup, ie. a lookup on the source IP address, in the BGP table
hence saying where it would route such traffic). pmacct offers a few ways to perform
some mapping to tackle this issue and easily model both private and public peerings,
both bi-lateral or multi-lateral. Find below how to use a map, reloadable at runtime,
and its contents (for full syntax guide lines, please see the 'peers.map.example'
file within the examples section):

```
bgp_peer_src_as_type: map
bgp_peer_src_as_map: /path/to/peers.map

[/path/to/peers.map]
set_tag=12345 ip=A.A.A.A in=10 bgp_nexthop=X.X.X.X
set_tag=34567 ip=A.A.A.A in=10

set_tag=45678 ip=B.B.B.B in=20 src_mac=00:11:22:33:44:55
set_tag=56789 ip=B.B.B.B in=20 src_mac=00:22:33:44:55:66
```

Even though all this mapping is static, it can be auto-provisioned to a good degree
by means of external scripts running at regular intervals and, for example, querying
relevant routers via SNMP. In this sense, the bgpPeerTable MIB is a good starting
point. Alternatively pmacct also offers the option to perform reverse BGP lookups.

### NOTES:
  
* When using maps, the peer_src_as primitive should be used with care if egress
  NetFlow/IPFIX/sFlow is in use as it mainly relies on either the input interface
  index (ifIndex), the source MAC address, a reverse BGP next-hop lookup or a
  combination of these. For example, egress NetFlow enabled on edge devices on
  core interfaces may work as the input ifIndex would still be visible; egress
  NetFlow enabled on edge devices on edge interfaces may not work as, unless
  traffic is locally switched, it may be sampled upon exiting the observed netowrk.
* "Source" MED, local preference, communities and AS-PATH have all been allocated
  aggregation primitives. Each carries its own peculiarities but the general concepts
  highlighed in this chapter apply to these aswell. Check CONFIG-KEYS out for the
  src_[med|local_pref|as_path|std_comm|ext_comm|lrg_comm]_[type|map] configuration
  directives.

## XIVc. Tracking entities on the own IP address space

It might happen that not all entities connected to the observed network are
running BGP but rather they get assigned provider IP prefixes redistributed
into iBGP (different routing protocols, statics, directly connected, etc.).
These can be private IP addresses or segments of the SP public address space.
The common factor to all of them is that while being present in iBGP, these
prefixes can't be distinguished any further due to the lack of attributes like
AS-PATH or an ASN. One simple solution, although costly, could be to account
on IP prefixes (other than BGP attributes). Another simple solution, especially
if the enity is dominated by outbound traffic (ingress in the observed network)
could be to use a bgp_peer_src_as_map directive, described previously (ie. make
use of interface descriptions as a possible way to automate the process).
Alternatively, bgp_stdcomm_pattern_to_asn and bgp_lrgcomm_pattern_to_asn config
directives were developed to fit in this scenario: assuming procedures of a SP
are (or can be changed) to label every relevant non-BGP speaking entity IP
prefixes uniquely with BGP standard communities, this directive then allows to
map the community to a peer AS/ origin AS couple as per the following example:

```
XXXXX:YYYYY => Peer-AS=XXXXX, Origin-AS=YYYYY. 
```

XIVd. Preparing the router to BGP peer 
Once the collector is configured and started up the remaining step is to let
routers export traffic samples to the collector and BGP peer with it. By
configuring the same source IP address across both NetFlow and BGP features
allows the collector to perform the required correlations without further
configuration. Also, setting the BGP Router ID accordingly allows for more
clear log messages. On the routers it is adviceable to configure the BGP
session with the collector as a Route-Reflector (RR) client.

A relevant configuration example for a Cisco IOS follows:

```
router bgp 12345
 neighbor X.X.X.X remote-as 12345
 neighbor X.X.X.X update-source Loopback12345
 neighbor X.X.X.X version 4
 neighbor X.X.X.X send-community
 neighbor X.X.X.X route-reflector-client
 neighbor X.X.X.X description nfacctd 

A relevant configuration example for a Juniper router follows:

protocols bgp {
    group rr-netflow {
        type internal;
        local-address Y.Y.Y.Y;
        family inet {
            any;
        }
        cluster Y.Y.Y.Y;
        neighbor X.X.X.X {
            description "nfacctd";
        }
    }
}
```

A relevant configuration example for a IOS XR (Version 5.1.1) router follows:

```
router bgp 12345
 address-family ipv4 unicast
  additional-paths receive
  additional-paths send
  maximum-paths ibgp 6
  additional-paths selection route-policy add_path
 !
 af-group af-group-example address-family ipv4 unicast
  route-reflector-client
 !
 session-group ibgp
  remote-as 12345
  update-source Loopback0
 !
 neighbor-group ibgp-rr-client
  use session-group ibgp
  address-family ipv4 unicast
   use af-group af-group-example
  !
 !
 neighbor X.X.X.X
  use neighbor-group ibgp-rr-client
 !
!
```

Contribution of further configuration examples for Cisco and Juniper devices
and/or other relevant vendors is more than welcome. 

In case ipv4 and ipv6 address-families are delivered over two distinct BGP
sessions, typically one with ipv4 transport and one with ipv6 transport, then,
since both ipv4 and ipv6 flows (NetFlow, IPFIX, sFlow) are typically delivered
over a single ipv4 transport, a bgp_agent_map is needed in order to make the
right correlation (see the 'filter' keyword in the example below). The map is
defined in the daemon configuration ie. 'bgp_agent_map: /path/to/bgp_agent.map'
then in the map itself for every router exporting flows and BGP peering the
following lines should be defined:

```
bgp_ip=<BGP v4 transport>	ip=<flow v4 transport>	filter='ip  or (vlan and ip)'
bgp_ip=<BGP v6 transport>	ip=<flow v4 transport>	filter='ip6 or (vlan and ip6)'
```

## XIVe. Example: writing flows augmented by BGP to a MySQL database

The following setup is a realistic example for collecting an external traffic
matrix to the ASN level (ie. no IP prefixes collected) for a MPLS-enabled IP
carrier network. Samples are aggregated in a way which is suitable to get an
overview of traffic trajectories, collecting much information where these enter
the AS and where they get out. 

```
daemonize: true
nfacctd_port: 2100
nfacctd_time_new: true

plugins: mysql[5mins], mysql[hourly]

sql_optimize_clauses: true
sql_dont_try_update: true
sql_multi_values: 1024000

sql_history_roundoff[5mins]: m
sql_history[5mins]: 5m
sql_refresh_time[5mins]: 300
sql_table[5mins]: acct_bgp_5mins

sql_history_roundoff[hourly]: h
sql_history[hourly]: 1h
sql_refresh_time[hourly]: 3600
sql_table[hourly]: acct_bgp_1hr

bgp_daemon: true
bgp_daemon_ip: X.X.X.X
bgp_daemon_max_peers: 100
bgp_aspath_radius: 3
bgp_follow_default: 1 
nfacctd_as: bgp
bgp_peer_src_as_type: map
bgp_peer_src_as_map: /path/to/peers.map

plugin_buffer_size: 10240
plugin_pipe_size: 1024000
aggregate: tag, src_as, dst_as, peer_src_as, peer_dst_as, peer_src_ip, peer_dst_ip, local_pref, as_path

pre_tag_map: /path/to/pretag.map
maps_refresh: true
maps_entries: 3840
```


The content of the maps (bgp_peer_src_as_map, pre_tag_map) is meant to be pretty
standard and will not be shown. As it can be grasped from the above configuration,
the SQL schema was customized. Below a suggestion on how this can be modified for
more efficiency - with additional INDEXes, to speed up specific queries response
time, remaining to be worked out:

```sql
create table acct_bgp_5mins (
        id INT(4) UNSIGNED NOT NULL AUTO_INCREMENT,
        agent_id INT(4) UNSIGNED NOT NULL,
        as_src INT(4) UNSIGNED NOT NULL,
        as_dst INT(4) UNSIGNED NOT NULL,
        peer_as_src INT(4) UNSIGNED NOT NULL,
        peer_as_dst INT(4) UNSIGNED NOT NULL,
        peer_ip_src CHAR(15) NOT NULL,
        peer_ip_dst CHAR(15) NOT NULL,
        as_path CHAR(21) NOT NULL,
        local_pref INT(4) UNSIGNED NOT NULL,
        packets INT UNSIGNED NOT NULL,
        bytes BIGINT UNSIGNED NOT NULL,
        stamp_inserted DATETIME NOT NULL,
        stamp_updated DATETIME,
        PRIMARY KEY (id),
        INDEX ...
) TYPE=MyISAM AUTO_INCREMENT=1;

create table acct_bgp_1hr (
        id INT(4) UNSIGNED NOT NULL AUTO_INCREMENT,
        agent_id INT(4) UNSIGNED NOT NULL,
        as_src INT(4) UNSIGNED NOT NULL,
        as_dst INT(4) UNSIGNED NOT NULL,
        peer_as_src INT(4) UNSIGNED NOT NULL,
        peer_as_dst INT(4) UNSIGNED NOT NULL,
        peer_ip_src CHAR(15) NOT NULL,
        peer_ip_dst CHAR(15) NOT NULL,
        as_path CHAR(21) NOT NULL,
        local_pref INT(4) UNSIGNED NOT NULL,
        packets INT UNSIGNED NOT NULL,
        bytes BIGINT UNSIGNED NOT NULL,
        stamp_inserted DATETIME NOT NULL,
        stamp_updated DATETIME,
        PRIMARY KEY (id),
        INDEX ...
) TYPE=MyISAM AUTO_INCREMENT=1;
```

Although table names are fixed in this example, ie. acct_bgp_5mins, it can be
highly adviceable in real-life to run dynamic SQL tables, ie. table names that
include time-related variables (see sql_table, sql_table_schema in CONFIG-KEYS). 

## XIVf. Example: exporting BGP tables or messaging to files or AMQP/Kafka brokers.

Both the stand-alone BGP collector daemon (pmbgpd) and the BGP thread within one
of the traffic accounting daemons can: a) export/dump routing tables for all BGP
peers at regular time intervals and b) log BGP messaging, real-time, with each
of the BGP peers. Both features are useful for producing data useful for
analytics, for troubleshooting and debugging. The former is beneficial to gain
visibility in extra BGP data while providing event compression; the latter
enables BGP analytics and BGP event management, for example spot unstable
routes, trigger alarms on route hijacks, etc. 

Both features export data formatted as JSON or Avro messages. Please review
the section "Compiling pmacct with JSON support" and, if planning to use Avro
encoding, also the section "Compiling pmacct with Avro support". If writing
to AMQP or Kafka brokers, compiling against RabbitMQ or Kafka libraries is
required; read more in respectively the "Running the RabbitMQ/AMQP plugin"
or "Running the Kafka plugin" sections of this document. If making use of the
Schema Registry component of the Confluent Platform please also review the
"Running the Kafka plugin" section. 

A basic dump of BGP tables at regular intervals (60 secs) to plain-text files,
split by BGP peer and time of the day, is configured as follows:

```
bgp_table_dump_file: /path/to/spool/bgp/bgp-$peer_src_ip-%H%M.txt
bgp_table_dump_refresh_time: 60
```

A basic log of BGP messaging in near real-time to a plain-text file (which can
be rotated by an external tool/script) is configured as follows:

```
bgp_daemon_msglog_file: /path/to/spool/bgp/bgp-$peer_src_ip.log
```

A basic dump of BGP tables at regular intervals (60 secs) to a Kafka broker,
listening on the localost and default port, is configured as follows:

```
bgp_table_dump_kafka_topic: pmacct.bgp
bgp_table_dump_refresh_time: 60
!
! [Optional] librdkafka config for buffer tuning, ssl config, etc. 
! bgp_table_dump_kafka_config_file: /path/to/librdkafka.conf
```

The equivalent bgp_table_dump_amqp_routing_key config directive can be used to
make the above example work against a RabbitMQ broker.

A basic log of BGP messaging in near real-time to a Kafka broker, listening on
the localhost and default port, is configured as follows:

```
bgp_daemon_msglog_kafka_topic: pmacct.bgp
!
! [Optional] librdkafka config for buffer tuning, ssl config, etc. 
! bgp_daemon_msglog_kafka_config_file: /path/to/librdkafka.conf
```

The equivalent bgp_daemon_msglog_amqp_routing_key config directive can be used
to make the above example work against a RabbitMQ broker.

A sample of both the BGP msglog and dump formats are captured in the following
document: docs/MSGLOG_DUMP_FORMATS


## XIVg. Example: querying the BGP daemon via the Looking Glass server.

The Looking Glass server allows to query RIBs stored in the BGP daemon. The
server is asyncronous and uses ZeroMQ as transport layer to serve incoming
queries. The LG server can be configured as follows:

```
bgp_daemon_lg: true
! bgp_daemon_lg_user: pmacct
! bgp_daemon_lg_passwd: arealsmartpwd 
```

This configuration will enable plain authentication and will make the server
listen on all interfaces on port 17900/TCP. Following an example of querying
with the Python client available in 'examples/lg':

Get the list of available BGP peers:

```shell
shell> examples/lg/pmbgp.py -g
{"results": 1, "query_type": 2}
{"peer_ip_src": "192.168.1.1", "peer_id": "192.168.1.1", "peer_tcp_port": 47248, "peer_as": 65500}
``` 

Lookup IP prefix 192.168.2.0/24 for BGP peer 192.168.1.1:

```shell
shell> examples/lg/pmbgp.py -a 192.168.2.0/24 -r 192.168.1.1
{"peer_ip_src": "192.168.1.1", "event_type": "lglass", "afi": 1, "safi": 1, "ip_prefix": "192.168.2.0/24", "bgp_nexthop": "192.168.1.254", "as_path": "65500 65501 65502", "comms": "65500:1 65500:100 65500:65500", "origin": 0, "local_pref": 100}
```

Request/Reply Looking Glass formats are documented in 'docs/LOOKING_GLASS_FORMAT'.

## XIVh. Example: BGP Xconnects 

pmbgpd, the pmacct BGP standalone daemon, includes a BGP xconnect feature
to map BGP peers (ie. routers) to BGP collectors (ie. nfacctd, sfacctd),
acting essentially as a BGP proxy. While the proxying is non-transparent,
BGP peers can be still identified by rheir BGP Router-ID. The aim of this
feature is to facilitate operations, ie. point all BGP Peers to a single
(or a couple) IP address(es) and facilitate re-sizing/re-balancing of the
collection infrastructure without impacting (ie. re-configuring) BGP peers.
A few caveats apply: 1) mapping works only against the IP source address
and not the BGP Router ID, 2) only 1:1 relationships can be formed (ie.
this is about cross-connecting sessions, not replication) and 3) only one
session per BGP peer is supported (ie. multiple BGP agents are running on
the same IP address or NAT traversal scenarios are not supported [yet]).
The feature can be configured as follows:

```
bgp_daemon_xconnect_map: /path/to/bgp_xconnects.map
```

And the content of the map can be defined as follows:

```
bgp_dst=10.0.0.1:17901  bgp_src=192.168.0.1
bgp_dst=10.0.0.1:17902  bgp_src=192.168.0.2
bgp_dst=10.0.0.1:17910  bgp_src=192.168.10.0/24
```

Where bgp_dst is the IPv4/IPv6 address and port of the BGP collector to cross-
connect incoming (bgp_src) BGP session to and bgp_src is compared against the
IPv4/IPv6 address (not BGP Router ID) of an incoming BGP session from a BGP
peer. At the collector end one should set tmp_bgp_lookup_compare_ports (read
more about this knob in CONFIG-KEYS) to true.

In future BMP may be added as a transport for BGP data between pmbgpd and the
collector (please get in touch if interested). An alternative to the use of
pmbgpd is NAT/masquerading; in this context, pmbgpd brings the advantage of
running fully in user-space.

SO_REUSEPORT feature (read more about it in the section "Miscellaneous notes
and troubleshooting tips" of this document) can be used in alternative to BGP
xconnects, ie. to simplify the deployment on a single node, or in conjunction
with BGP xconnects, ie. for massive multi-node scale-out.

Leveraging SO_REUSEPORT, when used in alternative to BGP xconnects, may be
best combined with a list of allowed IP addresses, ie. bgp_daemon_allow_file,
to explicitely wire peers to collectors. 

When SO_REUSEPORT is used in conjunction with BGP xconnects there is virtually
no config change to make (except perhaps the sensible decision to use different
'logfile' per pmbgpd daemon); below instead an example for SO_REUSEPORT in
alternative to BGP xconnects where a few nfacctd daemons are deployed each
running the BGP thread (indeed this is applicable to sfacctd as well):

## Daemon #1:

allow-1.map:

```
10.0.0.0/25
```

nfacctd-1.conf:

```
...
!
nfacctd_port: 2100
! nfacctd_allow_file: /path/to/allow-1.map
!
bgp_daemon: true
bgp_daemon_port: 179
bgp_daemon_allow_file: /path/to/allow-1.map
!
...
```

## Daemon #2:

allow-2.map:

```
10.0.0.128/25
```

nfacctd-2.conf:

```
...
!
nfacctd_port: 2101
! nfacctd_allow_file: /path/to/allow-2.map
!
bgp_daemon: true
bgp_daemon_port: 179
bgp_daemon_allow_file: /path/to/allow-2.map
!
...
```

NOTE: when leveraging SO_REUSEPORT for TCP sessions in conjunction with
allow files the kernel will try to naively balance the sessions over the
listening daemons; this may take a few connection attempts before wiring
the session to the right daemon; having an excessive numbers of daemons
in the pool may slow down the convergence process. 

NOTE: each xconnect requires two file descriptors, one for the inbound
TCP session, another for the outbound one. Popular default on Linux is
1024 descriptor per process, effectively limiting the amunt of sessions
that can be xconnected to approx 500. Such default can be adjusted via
'ulimit -n'.

For flow protocols, which are transported in UDP, a replication layer is
needed in front, note the daemon listen on different nfacctd_port in the
example above (read more on how to set up a replicator in the "Quickstart
guide to setup a NetFlow/IPFIX/sFlow replicator" section of the document).
nfacctd_allow_file is optional config key and, if created accordingly to
bgp_daemon_allow_file, may ensure only flows from router for which a BGP
sessions accepted should be processed.

## XIVi. Example: adding RPKI/ROA information 

Resource Public Key Infrastructure (RPKI) is a specialized public key
infrastructure (PKI) framework designed to secure the Internet routing. RPKI
uses certificates to allow Local Internet Registries (LIRs) to list the
Internet number resources they hold. These attestations are called Route
Origination Authorizations (ROAs). ROA information can be currently
acquired in one of the two following ways:

1. it can be imported using the rpki_roas_file config directive from a
   file in the RIPE Validator format, ie.:

   ```
{
  "roas" : [ {
    "asn" : "AS2914",
    "prefix" : "128.121.0.0/16",
    "maxLength" : 16,
    "ta" : "ARIN"
  }, {
    "asn" : "AS2914",
    "prefix" : "128.121.0.0/19",
    "maxLength" : 24,
    "ta" : "ARIN"
  }, {
    "asn" : "AS2914",
    "prefix" : "128.121.4.32/29",
    "maxLength" : 29,
    "ta" : "ARIN"
  } ]
}
   ```

  RPKI data in such format can be obtained for example at the following URL: [https://rpki.gin.ntt.net/api/export.json]().

1. Connecting to a RPKI RTR Cache for live ROA updates. Its IP address
   and port being defined by the rpki_rtr_cache config directive (a few
   more optional rpki_rtr_* directives are available and can be reviwed
   in the CONFIG-KEYS document).  

Once rpki_roas_file or rpki_rtr_cache are defined, traffic daemons (ie.
nfacctd) and pmbgpd can be configured to correlate traffic, BGP and RPKI
information. This is an example of how to configure nfacctd, the NetFlow/
IPFIX collector daemon:

```
nfacctd_as: longest
nfacctd_net: longest
! < .. >
!
! rpki_roas_file: /path/to/roas.json
!
rpki_rtr_cache: 127.0.0.1:8323
! rpki_rtr_cache_version: 1 
!
bgp_daemon: true
bgp_src_roa_type: bgp
! < .. > 
!
plugins: print[foo]
!
aggregate[foo]: peer_src_ip, peer_dst_ip, src_host, dst_host, src_roa, dst_roa
! < .. >
```

The ROA fields will be populated with one of these five values: 'u' Unknown,
'v' Valid, 'i' Invalid no overlaps, 'V' Invalid with a covering Valid prefix
and 'U' Invalid with a covering Unknown prefix.

## XIVl. BGP daemon implementation concluding notes

The implementation supports 4-bytes ASN, IPv4, IPv6, VPNv4 and VPNv6 (MP-BGP)
address families and several IETF drafts and RFCs, ie. ADD-PATH, Shutdown
Message and Large BGP Communities among the others; IPv4, IPv6 transports for
BGP sessions are supported. When storing data via SQL, BGP primitives can be
freely mix-and-matched with other primitives (ie. L2/L3/L4) when customizing
the SQL table (sql_optimize_clauses: true). Environments making use of BGP
Multi-Path should make use of ADD-PATH to advertise known paths in which case
the correct BGP info is linked to traffic data using BGP next-hop (or IP next-
hop if use_ip_next_hop is set to true) as selector among the paths available
(on the assumption that ADD-PATH is used for route diversity; all checked
implementations seem to tend to not advertise paths with the same next-hop).
TCP MD5 signature for BGP messages is also supported. For a review of all knobs
and features see the CONFIG-KEYS document. 


# XV. Quickstart guide to setup a NetFlow/IPFIX/sFlow replicator

The 'tee' plugin is meant to replicate NetFlow/sFlow data to remote collectors.
The plugin can act transparently, by preserving the original IP address of the
datagrams, or as a proxy. The basic configuration of a replicator is very easy:
all is needed is to define where to listen to for incoming packets, where to
replicate them to and optionally a filtering layer, if required. Filtering
bases on the standard pre_tag_map infrastructure; here will be presented only
coarse-grained filtering against the NetFlow/sFlow source IP address (see next
section for finer-grained filtering).

```
nfacctd_port: 2100
nfacctd_ip: X.X.X.X
!
plugins: tee[a], tee[b]
tee_receivers[a]: /path/to/tee_receivers_a.lst
tee_receivers[b]: /path/to/tee_receivers_b.lst
! tee_transparent: true
!
! pre_tag_map: /path/to/pretag.map
!
plugin_buffer_size: 10240
plugin_pipe_size: 1024000
nfacctd_pipe_size: 1024000
```

An example of content of a tee_receivers map, ie. /path/to/tee_receivers_a.lst,
is as follows ('id' is the pool ID and 'ip' a comma-separated list of receivers
for that pool):

```
id=1	ip=W.W.W.W:2100
id=2	ip=Y.Y.Y.Y:2100,Z.Z.Z.Z:2100
id=3	ip=[::1]:2100
! id=1	ip=W.W.W.W:2100			tag=0
! id=2	ip=Y.Y.Y.Y:2100,Z.Z.Z.Z:2100	tag=100
```

Number of tee_receivers map entries (by default 384) can be modified via
maps_entries. Content can be reloaded at runtime by sending the daemon a
SIGUSR2 signal (ie. "killall -USR2 nfacctd").

Selective teeing allows to filter which pool of receivers has to receive which
datagrams. Tags are applied via a pre_tag_map, the one illustrated below applies
tag 100 to packets exported from agents A.A.A.A, B.B.B.B and C.C.C.C; in case
there was also an agent D.D.D.D exporting towards the replicator, its packets
would intuitively remain untagged. Tags are matched by a tee_receivers map, see
above the two pool definitions commented out containing the 'tag' keyword: the
definition would cause untagged packets (tag=0) to be replicated only to pool #1 whereas packets tagged as 100 (tag=100) to be replicated only to pool #2.
More examples in the pretag.map.example and tee_receivers.lst.example files in
the *examples/* sub-tree:

```
set_tag=100	ip=A.A.A.A
set_tag=100	ip=B.B.B.B
set_tag=100	ip=C.C.C.C
```

To enable the transparent mode, the tee_transparent should be commented out. It
preserves the original IP address of the NetFlow/sFlow sender while replicating
by essentially spoofing it. This feature is not global and can be freely enabled
only on a subset of the active replicators. It requires super-user permissions
in order to run.

### Concluding note

The 'tee' plugin is not compatible with different plugins - within
the same daemon instance. So if in the need of using pmacct for both collecting
and replicating data, two separate instances must be used (intuitively with the
replicator instance feeding the collector one).

## XVa. Splitting and dissecting data while replicating

When replicating, it is possible to perform finer-grained filtering, ie.
against flow-specific primitives. For example: replicate flows from or to MAC
address X1, X2 .. Xn to receiver Y or replicate flows in VLAN W to receiver
Z. The feature works by inspecting the original packet and dissecting it as
needed, one of the most popular use-cases being IXPs replicating flows back
to the members originating and/or receiving them. The feature is available
for sFlow and NetFlow/IPFIX. Some of the supported primitives are: source/
destination MAC addresses and input/output interfaces ifindex; the full list
of primitives is available in examples/pretag.map.example (look for "sfacctd
when in 'tee' mode" or "nfacctd when in 'tee' mode").

The feature is configured just like selective teeing shown in the previous
section. Incoming packets are tagged with a pre_tag_map and then matched to a
receiver in tee_receivers. For example: replicate flows from/to MAC address
XX:XX:XX:XX:XX:XX to receiver Y, flows from/to MAC address WW:WW:WW:WW:WW:WW
to receiver Z and replicate any remaining (untagged) flows to receiver J.

This is the pre_tag_map map:

```
set_tag=100  ip=0.0.0.0/0	src_mac=XX:XX:XX:XX:XX:XX
set_tag=100  ip=0.0.0.0/0	dst_mac=XX:XX:XX:XX:XX:XX
set_tag=200  ip=0.0.0.0/0	src_mac=WW:WW:WW:WW:WW:WW
set_tag=200  ip=0.0.0.0/0	dst_mac=WW:WW:WW:WW:WW:WW
set_tag=999  ip=0.0.0.0/0
```

This is the tee_receivers map:

```
id=100		ip=Y.Y.Y.Y:2100	tag=100
id=200		ip=Z.Z.Z.Z:2100	tag=200
id=999		ip=J.J.J.J:2100	tag=999
```

This is the relevant section from nfacctd/sfacctd configuration:

```
[ .. ]
!
tee_transparent: true
maps_index: true
!
plugins: tee[a]
!
tee_receivers[a]: /path/to/tee_receivers.lst
pre_tag_map[a]: /path/to/pretag.map
```

Along with dissected flows, it is possible to replicate also the original
packet as-is. This can be done in a separate 'tee' plugin with no or a
simple pre_tag_map defined. Extending the example above, we instantiate
two plugins; 'a' is as per the previous example, 'b' is to replicate full
packets (as in plain, non-dissected replication):

```
[ .. ]
!
tee_transparent: true
maps_index: true
!
plugins: tee[a], tee[b]
!
tee_receivers[a]: /path/to/tee_receivers_a.lst
pre_tag_map[a]: /path/to/pretag_a.map
!
tee_receivers[a]: /path/to/tee_receivers_b.lst
pre_tag_map[a]: /path/to/pretag_b.map
```

tee_receivers_a.lst and pretag_a.map are precisely as in the previous
example. 

This is the pretag_b.map map:

```
set_tag=100	ip=0.0.0.0/0
```

This is the tee_receivers_b.map map:

```
id=100		ip=H.H.H.H:2100	tag=100
```

Defining a simple pre_tag_map as one where no entries require dissecting
flows (ie. tagging on source_id, agent_id, ip, etc. keys) and a complex
pre_tag_map as one that requires dissecting flows (ie. tagging on vlan,
src_mac, dst_net, etc. keys) this is the table of truth for stopping or
passing replicated data:

```
	   no pre_tag_map | simple pre_tag_map | complex pre_tag_map
			  |		       |
dissected	no	  |        no	       |         yes
			  |		       |
     full	yes	  |	   yes	       |	 no
```

There are a few restrictions to the feature: 1) for sFlow, only sFlow v5 flow
samples are supported, ie. no sFlow v2/v4 nor counter samples; 2) for NetFlow/
IPFIX, templates and option data is broadcasted to configured tee receivers
(regardless of tags); 3) once split, flows are not muxed back together, ie.
in case multiple samples part of the same packet are to be replicated to the
same receiver; 4) sequence numbers are untouched: the most obvious cases being
receivers may detect non-increasing sequencing or false duplicates. If you are
negatively affected by any of these restrictions or limitations or you need
other primitives to be supported by this feature, please get in touch.


# XVI. Quickstart guide to setup the IS-IS daemon

pmacct integrates an IS-IS daemon as part of the IP accounting collectors. Such
daemon is run as a thread within the collector core process. The idea is to
receive data-plane information, ie. via NetFlow, sFlow, etc., and control-plane
information via IS-IS. Currently a single L2 P2P neighborship, ie. over a GRE
tunnel, is supported. The daemon is currently used for the purpose of route
resolution. A sample scenario could be that more specific internal routes might
be configured to get summarized in BGP while crossing cluster boundaries.  

Pre-requisite for the use of the IS-IS daemon is that the pmacct package has to
be configured for compilation with threads, this line will do it:

```
shell> ./configure
```

## XVIa. Preparing the collector for the L2 P2P IS-IS neighborship

It's assumed the collector sits on an Ethernet segment and has not direct link
(L2) connectivity to an IS-IS speaker, hence the need to establish a GRE tunnel. 
While extensive literature and OS specific examples exist on the topic, a brief
example for Linux, consistent with rest of the chapter, is provided below:

```
ip tunnel add gre2 mode gre remote 10.0.1.2 local 10.0.1.1 ttl 255
ip link set gre2 up
```

The following configuration fragment is sufficient to set up an IS-IS daemon
which will bind to a network interface gre2 configured with IP address 10.0.1.1
in an IS-IS area 49.0001 and a CLNS MTU set to 1400:

```
isis_daemon: true
isis_daemon_ip: 10.0.1.1
isis_daemon_net: 49.0001.0100.0000.1001.00
isis_daemon_iface: gre2
isis_daemon_mtu: 1400
! isis_daemon_msglog: true
```

## XVIb. Preparing the router for the L2 P2P IS-IS neighborship 

Once the collector is ready, the remaining step is to configure a remote router
for the L2 P2P IS-IS neighborship. The following bit of configuration (based on
Cisco IOS) will match the above fragment of configuration for the IS-IS daemon:

```
interface Tunnel0
 ip address 10.0.1.2 255.255.255.252
 ip router isis
 tunnel source FastEthernet0
 tunnel destination XXX.XXX.XXX.XXX
 clns mtu 1400
 isis metric 1000
!
router isis
 net 49.0001.0100.0000.1002.00
 is-type level-2-only
 metric-style wide
 log-adjacency-changes
 passive-interface Loopback0
!
```

# XVII. Quickstart guide to setup the BMP daemon

BMP can be run as a stand-alone collector daemon (pmbmpd) or as a thread
within one of the traffic accounting daemons (ie. nfacctd). The stand-alone
daemon is suitable for consuming BMP data only, real-time or at regular
intervals; the thread solution is suitable for correlation of BMP with other
data sources, ie. NetFlow, IPFIX, sFlow, etc.. The implementation bases on
rfc7854 and is in-sync with most recent RFCs and draft-ietf-grow-bmp-* IETF
documents (ie. rfc8671, ietf-grow-bmp-local-rib, ietf-grow-bmp-tlv, etc.).

If unfamiliar with BMP, to quote rfc7854: "BMP is intended to provide a more
convenient interface for obtaining route views for research purpose than the
screen-scraping approach in common use today. The design goals are to keep
BMP simple, useful, easily implemented, and minimally service-affecting.".

The BMP daemon currently supports BMP data, events and stats, ie. initiation,
termination, peer up, peer down, stats and route monitoring messages (that is
no route mirroring messages; please get in touch if an implementation is
wanted in this sense). The daemon enables to write BMP messages to files, AMQP
and Kafka brokers, real-time (msglog) or at regular time intervals (dump).
Also, route monitoring messages are saved in a RIB structure for IP prefix
lookup.

All features export data formatted as JSON or Avro messages. Please review
the section "Compiling pmacct with JSON support" and, if planning to use Avro
encoding, also the section "Compiling pmacct with Avro support". If writing
to AMQP or Kafka brokers, compiling against RabbitMQ or Kafka libraries is
required; read more in respectively the "Running the RabbitMQ/AMQP plugin"
or "Running the Kafka plugin" sections of this document. If making use of the
Schema Registry component of the Confluent Platform please also review the
"Running the Kafka plugin" section.

Following a simple example on how to configure nfacctd to enable the BMP thread
to a) log, in real-time, BGP stats, events and routes received via BMP to a
text-file (bmp_daemon_msglog_file) and b) dump the same (ie. BGP stats and
events received via BMP) to a text-file and at regular time intervals
(bmp_dump_refresh_time, bmp_dump_file):

```
bmp_daemon: true
!
bmp_daemon_msglog_file: /path/to/bmp-$peer_src_ip.log
!
bmp_dump_file: /path/to/bmp-$peer_src_ip-%H%M.dump
bmp_dump_refresh_time: 60
```

Following a simple example on how to configure nfacctd to enable the BMP thread
to a) log, in real-time, BGP stats, events and routes received via BMP to a
Kafka broker (bmp_daemon_msglog_kafka_topic) and b) dump the same (ie. BGP stats
and events received via BMP) to a text-file and at regular time intervals
(bmp_dump_refresh_time, bmp_dump_kafka_topic):

```
bmp_daemon: true
!
bmp_daemon_msglog_kafka_topic: pmacct.bmp-msglog
!
bmp_dump_kafka_topic: pmacct.bmp-dump
bmp_dump_refresh_time: 60
!
! [Optional] librdkafka config for buffer tuning, ssl config, etc. 
! bmp_dump_config_file: /path/to/librdkafka.conf
```

The equivalent bmp_daemon_msglog_amqp_routing_key and bmp_dump_amqp_routing_key
config directives can be used to make the above example work against a RabbitMQ
broker.

A sample of both the BMP msglog and dump formats are captured in the following
document: docs/MSGLOG_DUMP_FORMATS

Setting up the stand-alone BMP collector daemon, pmbmpd, is the exact same as
the configuration above except the 'bmp_daemon: true' line can be skipped.

Following is an example of how a Cisco router running IOS/IOS-XE (15.4(2)T) should be
configured in order to export BMP data to a collector:

```
router bgp 64512
 bmp server 1
  address X.X.X.X port-number 1790
  initial-delay 60
  failure-retry-delay 60
  flapping-delay 60
  stats-reporting-period 300
  activate
 exit-bmp-server-mode
 !
 neighbor Y.Y.Y.Y remote-as 64513
 neighbor Y.Y.Y.Y bmp-activate all
 neighbor Z.Z.Z.Z remote-as 64514
 neighbor Z.Z.Z.Z bmp-activate all
```

Following is an example how a Cisco router running IOS-XR (6.2.1) should be configured
in order to export BMP data to a collector:

```
router bgp 64512
 neighbor Y.Y.Y.Y
  bmp-activate server 1
 neighbor Z.Z.Z.Z
  bmp-activate server 1
 !
!
bmp server 1
 host X.X.X.X port 1790
 description -- fretta --
 update-source GigabitEthernet0/0/0/10
 initial-delay 60
 initial-refresh delay 60
 stats-reporting-period 300
 initial-refresh delay 10
!
```

Following is an example how a Juniper router should be configured in order to
export BMP data to a collector:

```
routing-options {
	bmp {
		station FQDN {
			connection-mode active;
       			monitor enable;
			route-monitoring {
				pre-policy;
				post-policy;
			}
			station-address X.X.X.X;
			station-port 1790;
		}
	}
}
```

Following is an example how a Huawei router should be configured in order to
export BMP data to a collector:

```
bmp
 statistics-timer 3600
 #
 bmp-session 192.0.2.1
  tcp connect port 1790
  connect-interface GigabitEthernet0/3/6
  #
  monitor peer 198.51.100.19
   route-mode ipv4-family vpnv4 adj-rib-in pre-policy
   route-mode ipv4-family vpnv4 adj-rib-in post-policy
   route-mode ipv4-family vpnv4 adj-rib-out pre-policy
   route-mode ipv4-family vpnv4 adj-rib-out post-policy
  #
  monitor peer 198.51.100.25
   route-mode ipv4-family vpnv4 adj-rib-in pre-policy
   route-mode ipv4-family vpnv4 adj-rib-in post-policy
   route-mode ipv4-family vpnv4 adj-rib-out pre-policy
   route-mode ipv4-family vpnv4 adj-rib-out post-policy
  #
  monitor vpn-instance A
   route-mode ipv4-family unicast local-rib
```

Contribution of further configuration examples for Cisco and Juniper devices
and/or other relevant vendors is more than welcome.
 

# XVIII. Quickstart guide to setup Streaming Telemetry collection

Quoting Cisco IOS-XR Telemetry Configuration Guide at the time of this writing:
"Streaming telemetry lets users direct data to a configured receiver. This data
can be used for analysis and troubleshooting purposes to maintain the health of
the network. This is achieved by leveraging the capabilities of machine-to-
machine communication. The data is used by development and operations (DevOps)
personnel who plan to optimize networks by collecting analytics of the network
in real-time, locate where problems occur, and investigate issues in a
collaborative manner.". Streaming telemetry support comes in pmacct in two
flavours: 1) a telemetry thread can be started in existing daemons, ie. sFlow,
NetFlow/IPFIX, etc. for the purpose of data correlation and 2) a new daemon
pmtelemetryd for standalone consumpton of data. Streaming telemetry data can
be logged real-time and/or dumped at regular time intervals to flat-files,
RabbitMQ or Kafka brokers.

All features export data formatted as JSON messages, hence compiling pmacct
against libjansson is a requirement. See how to compile pmacct with JSON/
libjansson support in the section "Compiling pmacct with JSON support" of this
document. If writing to AMQP or Kafka brokers compiling against RabbitMQ or
Kafka libraries is required; read more in respectively the "Running the
RabbitMQ/AMQP plugin" or "Running the Kafka plugin" sections of this document.

Data can be optionally consumed from a ZeroMQ queue, for example to have a
pre-processor taking care of the GPB (Protobuf or Google Protocol Buffers) 
de-marshalling and conversion to JSON; read more about (compiling) ZeroMQ in
the "Internal buffering and queueing" section of this document; also read more
about gRPC support and GPB de-marshalling in telemetry/README.telemetry .

From a configuration standpoint both the thread (ie. telemetry configured part
of nfacctd) and the daemon (pmtelemetryd) are configured the same way except the
thread must be explicitely enabled with a 'telemetry_daemon: true' config line.
Hence the following examples hold for both the thread and the daemon setups.  

Following is a config example to receive telemetry data in JSON format over UDP
port 1620 and log it real-time to flat-files:

```
! Telemetry thread configuration
! telemetry_daemon: true 
!
telemetry_daemon_port_udp: 1620
telemetry_daemon_decoder: json
!
telemetry_daemon_msglog_file: /path/to/spool/telemetry-msglog-$peer_src_ip.txt
! telemetry_daemon_msglog_amqp_routing_key: telemetry-msglog
! telemetry_daemon_msglog_kafka_topic: telemetry-msglog
```

Following is a config example to receive telemetry data with Cisco proprietary
header, in GPB format over TCP port 1620 and dump it at 60 secs time intervals
to flat-files:

```
! Telemetry thread configuration
! telemetry_daemon: true
!
telemetry_daemon_port_tcp: 1620
telemetry_daemon_decoder: cisco_v1
!
telemetry_dump_file: /path/to/spool/telemetry-dump-$peer_src_ip-%Y%m%d-%H%M.txt
telemetry_dump_latest_file: /path/to/spool/telemetry-dump-$peer_src_ip.latest
! telemetry_dump_amqp_routing_key: telemetry-dump
! telemetry_dump_kafka_topic: telemetry-dump
!
! [Optional] librdkafka config for buffer tuning, ssl config, etc. 
! telemetry_dump_kafka_config_file: /path/to/librdkafka.conf
!
telemetry_dump_refresh_time: 60
```

Following is a config example to receive JSON-formatted telemetry data from a
pre-processor over a ZeroMQ queue (see telemetry/README.telemetry for further 
info, ie. gRPC support and GPB de-marshalling):

```
! Telemetry thread configuration
! telemetry_daemon: true
!
telemetry_daemon_zmq_address: 127.0.0.1:50000
telemetry_daemon_decoder: json
!
telemetry_daemon_msglog_file: /path/to/spool/telemetry-msglog-$peer_src_ip.txt
! telemetry_daemon_msglog_amqp_routing_key: telemetry-msglog
! telemetry_daemon_msglog_kafka_topic: telemetry-msglog
!
! [Optional] librdkafka config for buffer tuning, ssl config, etc. 
! telemetry_daemon_msglog_kafka_config_file: /path/to/librdkafka.conf
```

A sample of both the Streaming Telemetry msglog and dump formats are captured in
the following document: docs/MSGLOG_DUMP_FORMATS


# XIX. Running the print plugin to write to regular files and named pipes
pmacct can also output to regular files and named pipes via the 'print' plugin.
Dynamic filenames are supported. Output encoding is either text-based using
JSON or CSV or binary schema-based using Apache Avro; encoding can be set
via the 'print_output' config directive.

Interval between writes can be configured via the 'print_refresh_time' config
directive. An example follows on how to write to regular files in CSV format,
every 15 minutes and aggregate data in 15 minutes time-bins (print_history):

```
print_refresh_time: 900
print_history: 15m
print_output: csv
print_output_file: /path/to/file-%Y%m%d-%H%M.txt
print_history_roundoff: m
``` 

Which, over time, would produce a series of files as follows:

```
-rw-------  1 paolo paolo   2067 Nov 21 00:15 blabla-20111121-0000.txt
-rw-------  1 paolo paolo   2772 Nov 21 00:30 blabla-20111121-0015.txt
-rw-------  1 paolo paolo   1916 Nov 21 00:45 blabla-20111121-0030.txt
-rw-------  1 paolo paolo   2940 Nov 21 01:00 blabla-20111121-0045.txt
```

JSON output requires compiling pmacct against Jansson library. See how to
compile pmacct with JSON/libjansson support in the section "Compiling pmacct
with JSON support" of this document.

Avro output requires compiling pmacct against libavro library. See how to
compile pmacct with Avro support in the section "Compiling pmacct with Apache
Avro support" of this document.

Splitting data into time-bins is supported via print_history directive. When
enabled, time-related variable substitutions of dynamic print_output_file names
are determined using this value. It is supported to define print_refresh_time
values shorter than print_history ones by setting print_output_file_append to
true (which is generally also recommended to prevent that unscheduled writes to
disk, ie. due to caching issues, overwrite existing file content). A sample
config follows:

```
print_refresh_time: 300
print_output: csv
print_output_file: /path/to/%Y/%Y-%m/%Y-%m-%d/file-%Y%m%d-%H%M.txt
print_history: 15m
print_history_roundoff: m
print_output_file_append: true 
```

Writing to named pipes is an easy way to stream data into 3rd party tools
without adding external dependencies (ie. RabbitMQ, Kafka). The named pipe
must be manually created before starting the pmacct daemon. From a config
standpoint using a named pipe is transparent and hence all the examples
provided so far in this section do apply to named pipes as well.  

Writing to regular files is a suitable method to batch ingest data into
3rd party tools (typically, but not limited to, modern noSQL databases like
ElasticSearch, InfluxDB, etc.). An example is the pmacct-to-elasticsearch
project https://github.com/pierky/pmacct-to-elasticsearch . 


# XX. Quickstart guide to setup GeoIP lookups
pmacct can perform GeoIP country lookups against a Maxmind DB v1 (--enable-geoip)
and against a Maxmind DB v2 (--enable-geoipv2). A v1 database enables resolution
of src_host_country and dst_host_country primitives only. A v2 database enables
resolution of presently supported GeoIP-related primitives, ie. src_host_country,
src_host_pocode, src_host_coords, dst_host_country, dst_host_pocode and
dst_host_coords. Pre-requisite for the feature to work are: a) a working
installed Maxmind GeoIP library and headers and b) a Maxmind GeoIP database
(freely available). Two steps to quickly start with GeoIP lookups in pmacct:
 
### GeoIP v1 (libGeoIP):

* Have libGeoIP library and headers available to compile against; have a GeoIP
  database also available: http://dev.maxmind.com/geoip/legacy/install/country/ 

* To compile the pmacct package with support for GeoIP lookups, the code must
  be configured for compilation as follows:

  ```shell
  shell> ./configure --enable-geoip [ ... ]
  ```

  But, for example, should you have installed libGeoIP in /usr/local/geoip and
  pkg-config is unable to help, you can supply this non-default location as
  follows (assuming you are running the bash shell):

  ```shell
  shell> export GEOIP_LIBS="-L/usr/local/geoip/lib -lgeoip"
  shell> export GEOIP_CFLAGS="-I/usr/local/geoip/include"
  shell> ./configure --enable-geoip [ ... ]
  ```
  
* Include as part of the pmacct configuration the following fragment:
  
  ```
  ...
  geoip_ipv4_file: /path/to/GeoIP/GeoIP.dat  
  aggregate: src_host_country, dst_host_country, ...
  ...
  ```

### GeoIP v2 (libmaxminddb):

* Have libmaxminddb library and headers to compile against, available at:
  https://github.com/maxmind/libmaxminddb/releases ; have also a database
  available: https://dev.maxmind.com/geoip/geoip2/geolite2/ . Only the
  database binary format is supported.

* To compile the pmacct package with support for GeoIP lookups, the code must
  be configured for compilation as follows:

  ```shell
  shell> ./configure --enable-geoipv2 [ ... ]
  ```

  But, for example, should you have installed libmaxminddb in /usr/local/geoipv2
  and pkg-config is unable to help, you can supply this non-default location
  as follows (assuming you are running the bash shell):
  
  ```shell
  shell> export GEOIPV2_LIBS="-L/usr/local/geoipv2/lib -lmaxminddb"
  shell> export GEOIPV2_CFLAGS="-I/usr/local/geoipv2/include"
  shell> ./configure --enable-geoipv2 [ ... ]
  ```

* Include as part of the pmacct configuration the following fragment:

  ```
  ...
  geoipv2_file: /path/to/GeoIP/GeoLite2-Country.mmdb
  aggregate: src_host_country, dst_host_country, ...
  ...
  ```

### Concluding notes: 

1. The use of --enable-geoip is mutually exclusive with
--enable-geoipv2;
1. More fine-grained GeoIP lookup primitives (ie. cities,
states, counties, metro areas, zip codes, etc.) are not yet supported: should
you be interested into any of these, please get in touch.  


# XXI. Using pmacct as traffic/event logger

This use-case has been fostered particularly by the use of NetFlow/IPFIX as
generic transport, see for example Cisco NEL and Cisco NSEL. Key to logging
are time-stamping primitives, timestamp_start and timestamp_end: the former
records the likes of libpcap packet timestamp, sFlow sample arrival time,
NetFlow observation time and flow first switched time; timestamp_end does
currently only makes sense for logging flow data via NetFlow/IPFIX. Still,
the exact boundary between aggregation and logging can be defined via the
aggregation method, ie. no assumptions are made. An example to log traffic
flows follows:

```
! ...
!
plugins: print[traffic] 
!
aggregate[traffic]: src_host, dst_host, peer_src_ip, peer_dst_ip, in_iface, out_iface, timestamp_start, timestamp_end, src_port, dst_port, proto, tos, src_mask, dst_mask, src_as, dst_as, tcpflags
print_output_file[traffic]: /path/to/traffic-%Y%m%d_%H%M.txt
print_output[traffic]: csv
print_history[traffic]: 5m
print_history_roundoff[traffic]: m
print_refresh_time[traffic]: 300
! print_cache_entries[traffic]: 9999991
print_output_file_append[traffic]: true
!
! ...
```

An example to log specifically CGNAT (Carrier Grade NAT) events from a
Cisco ASR1K box follows:

```
! ...
!
plugins: print[nat]
!
aggregate[nat]: src_host, post_nat_src_host, src_port, post_nat_src_port, proto, nat_event, timestamp_start
print_output_file[nat]: /path/to/nat-%Y%m%d_%H%M.txt
print_output[nat]: json
print_history[nat]: 5m
print_history_roundoff[nat]: m
print_refresh_time[nat]: 300
! print_cache_entries[nat]: 9999991
print_output_file_append[nat]: true
!
! ...
```

The two examples above can intuitively be merged in a single configuration
so to log down in parallel both traffic flows and events. To split flows
accounting from events, ie. to different files, a pre_tag_map and two print
plugins can be used as follows:

```
! ...
!
pre_tag_map: /path/to/pretag.map
!
plugins: print[traffic], print[nat]
!
pre_tag_filter[traffic]: 10
aggregate[traffic]: src_host, dst_host, peer_src_ip, peer_dst_ip, in_iface, out_iface, timestamp_start, timestamp_end, src_port, dst_port, proto, tos, src_mask, dst_mask, src_as, dst_as, tcpflags
print_output_file[traffic]: /path/to/traffic-%Y%m%d_%H%M.txt
print_output[traffic]: csv
print_history[traffic]: 5m 
print_history_roundoff[traffic]: m 
print_refresh_time[traffic]: 300
! print_cache_entries[traffic]: 9999991
print_output_file_append[traffic]: true
!
pre_tag_filter[nat]: 20
aggregate[nat]: src_host, post_nat_src_host, src_port, post_nat_src_port, proto, nat_event, timestamp_start 
print_output_file[nat]: /path/to/nat-%Y%m%d_%H%M.txt
print_output[nat]: json
print_history[nat]: 5m 
print_history_roundoff[nat]: m 
print_refresh_time[nat]: 300
! print_cache_entries[nat]: 9999991
print_output_file_append[nat]: true
!
! ...
```

In the above configuration both plugins will log their data in 5 mins files
basing on the 'print_history[<plugin name>]: 5m' configuration directive, ie.
traffic-20130802-1345.txt traffic-20130802-1350.txt traffic-20130802-1355.txt
etc. Granted appending to output file is set to true, data can be refreshed
at shorter intervals than 300 secs. This is a snippet from /path/to/pretag.map
referred above:

```
set_tag=10      ip=A.A.A.A	sample_type=flow
set_tag=20      ip=A.A.A.A	sample_type=event
set_tag=10      ip=B.B.B.B	sample_type=flow
set_tag=20      ip=B.B.B.B	sample_type=event
!
! ...
```

# XXII. Connecting pmacct to a Redis cache

Since version 1.7.5, pmacct daemons can connect to a Redis cache. The main
use-case currenly covered is: registering every stable daemon component (ie.
plugins, threads, etc. but not writers for example) in a table so to have,
when running a cluster comprising several daemons / components, an olistic
view of what is currently running and where; shall a component stop running
or crash it will disappear from the inventory.

Over time it is expected that the amount of use-cases will increase to include
specific features where one daemon can obtain relevant information about other
daemons running in the cluster.

Requirement to use the Redis feature plugin is the Hiredis library available
here: https://github.com/redis/hiredis . Once this is installed, pmacct can
be configured for compiling. pmacct makes use of pkg-config for finding
libraries and headers location and checks some default locations, ie.
/usr/local/lib and /usr/local/include. If this is satisfactory, all you
should do is just:

```
shell> ./configure --enable-redis
```

But, for example, should you have installed Hiedis in /usr/local/redis and
pkg-config is unable to help, you can supply this non-default location as
follows (assuming you are running the bash shell):

```
shell> export REDIS_LIBS="-L/usr/local/redis/lib -lhiredis"
shell> export EDIS_CFLAGS="-I/usr/local/redis/include"
shell> ./configure --enable-redis
```

Following a configuration snippet showing a basic configuration for the
Redis feature. redis_host points to the Redis cache whereas cluster_*
directives essentially form a pmacct cluster (cluster_name, every cluster
should have a different name string, and cluster_id, an unique id inside
a certain cluster):

```
cluster_name: prod 
cluster_id: 1
!
redis_host: 127.0.0.1:6379
```


# XXIII. Miscellaneous notes and troubleshooting tips

This chapter will hopefully build up to the point of providing a taxonomy of
popular cases to troubleshoot by daemon and what to do. Although that is the
plan, the current format is sparse notes.  

When reporting a bug: please report in all cases the pmacct version that you
are experiencing your issue against; the CLI option -V of the daemon you are
using returns all the info needed (daemon, version, specific release and
options compiled in). Do realise that if using a pre-packaged version from
your OS and/or old code (ie. not master code on GitHub or latest official
release), you may be very possibly asked to try one of these first. Finally,
please refrain to open issues on GitHub if not using master code (use the
pmacct-discussion mailing list or unicast email instead). 

1. In cases of errors at configure script time (ie. library not found, headers
  not found, etc.), additional info can be found in config.log at the end of
  the 'Core tests' section. Also if reporting an issue related to configure
  time, it is good idea to supply the config.log file as well. Here are recap
  some popular issues when compiling pmacct or linking it at runtime against
  shared libraries:

  1. /usr/local/sbin/pmacctd: error while loading shared libraries:
     librabbitmq.so.4: cannot open shared object file: No such file or directory 

     This can happen at runtime and, especially in case of freshly downloaded
     and compiled libraries, it is a symptom that after installing the shared
     library, ldconfig was not called. Or alternatively that the directory
     where the library is located is not inserted in /etc/ld.so.conf or in any
     files included it includes. When not having super-user privileges, this
     can be fixed in the own environment setting the LD_LIBRARY_PATH variable.

  1. json_array_foreach(json_list, key, value) {
                                               ^
     nfv9_template.c: In function ‘nfacctd_offline_read_json_template’:
     nfv9_template.c:572:53: error: expected ‘;’ before ‘{’ token

     This can happen at compile time and and is a bit tricky to hint. In this
     example the function json_array_foreach() is not being recognized, in
     other words while the library could be located, it does not contain the
     specific function. This is a symptom that the library version in use is
     too old. Typical situation is when using a packaged library rather than
     a freshly downloaded and compiled latest stable release. 

  1. /usr/local/lib/libpcap.so: undefined reference to `pcap_lex'
     collect2: error: ld returned 1 exit status
     make[2]: *** [pmacctd] Error 1

     This can happen at compile time and it is a symptom that the needed
     library could not be located by the linker. This is a symptom that the 
     library could be in some non-standard location and the linked need an
     hint. For libpcap --with-pcap-libs knob is available at configure time;
     for all other libraries the library_LIBS and library_CFLAGS environment
     variables are available. See examples in the "Configuring pmacct for
     compilation and installing" section of this document.

1. In case of crashes of an any process, regardless if predictable or not, the
advice is to run the daemon with "ulimit -c unlimited" so to generate a core
dump. The core dump file location, on Linux, is determined by the following
file: /proc/sys/kernel/core_pattern : if the value is "core", then the file is
placed in the directory where the daemon is started so it is good to take care
of that. pmacct developers will then ask for one or both of the following: 1)
the core file along with the crashing executable and its configuration be made
available for further inspection and/or 2) a backtrace in GDB obtained via the
following two steps:

  ```
  shell> gdb /path/to/executable /path/to/core
  ```

  Then once in the gdb console the backtrace output can be obtained with the following command:

  ```
  gdb> bt
  ```

  As an alternative to gdb, the valgrind tool can be used which, upon crashing, will simply print out the backtrace:

  ```
  shell> valgrind /path/to/executable <command-line options>
  ```

  If the dmesg command or system logs reveal a line like the following one:

  ```
  Jan 01 00:00:00 xxxx kernel: [4075819.569587] nfacctd[51817]: segfault at 10 ip 00007f77f448ad44 sp 00007ffc6974ed70 error 4 ..
  ```

  In certain cases, ie. if the crash is not inside a shared library, this can return useful information for debugging when examined with addr2line; using the example above:

  ```
  shell> addr2line /path/to/nfacctd 00007f77f448ad44
  ```

  Optionally, especially if the issue can be easily reproduced, the daemon can be re-configured for compiling with the *--enable-debug* flag so to produce extra info suitable for troubleshooting. 

  There is a whole range of cases where the crash could be caused by corrupting the heap and these are evidenced when a 'bt' in gdb highlights a malloc() call as point of crash; while these issues often times boil down to erroneous coding, they are subtle, hard to reproduce and platform / OS dependant. When facing
such issues, launching the daemon with the MALLOC_CHECK_ environment variable set to 2, ie.:

  ```
  shell> MALLOC_CHECK_=2
  shell> export MALLOC_CHECK_
  ```

  Would return additional useful information for the troubleshooting process. At times this action - that elicits the use of an alternate malloc() call - may even work as a work-around (if falling in this condition it is recommended to not use this 'mask' as long-term solution, that is, please report the issue).

  The use of Docker containers is getting increasingly popular. The valgrind tool can be used when a crash is experienced in a container. The following example applies to any of the official pmacct containers (running on top of Debian):

  ```
  shell> docker run -it --entrypoint bash <image_name>
  <container_id># apt-get update && apt-get install -y valgrind
  <container_id># valgrind /path/to/executable <command-line options>
  ```

1. In case of (suspected) memory leaks, the advice is to: 1) re-compile pmacct with "./configure --enable-debug <other flags already in use>"; --enable-debug sets as CFLAGS -O0 -g -Wall where especially -O0 is capital since it disables any code optimizations the compiler may introduce; 2) run the resulting daemon under valgrind, "valgrind --leak-check=yes /path/to/executable <command-line options>". A memory leak is confirmed if the amount of "definitely lost" bytes keeps increasing over time.

1. In the two cases of nfacctd/sfacctd or nfprobe/sfprobe not showing signs of
input/output data: 

	1. check with tcpdump, ie. 
     
     ```
     tcpdump -i <interface> -n port <sfacctd/nfacctd listening port>
     ``` 
     (for uacctd use -i nflog:<nflog group>), that packets are emitted/received. Optionally Wireshark (or its cli tool tshark) can be used, in conjunction with decoders ('cflow' for NetFlow/IPFIX and 'sflow' for sFlow), to validate packets are consistent; this proofs there is no filtering taking place in between exporters and collector; 
     
   2. check firewall settings on the collector box, ie. 

      ```
      iptables -L -n" 
      ```
      
      on Linux (disable or do appropriate holes): tcpdump may see packets hitting the listening port as, in normal kernel operations, the filtering happens after the raw socket (the one used by tcpdump) is served; you can also check with 3rd party equivalent tools or netcat, 
      
      ```
      nc -l -u -p <port>
      ```
      
	   that the same behaviour is obtained as with pmacct; finally, if running on a SELinux enabled system, consider that it could be interfering too;
   3. when not using ZeroMQ for internal buffering (plugin_pipe_zmq set to true) and especially in case of copy/paste of configs or if using a config from a production system in lab, disable/double-check values for internal buffering: if set too high they will likely retain data internally to the daemon;
   4. If multiple interfaces are configured on a system, try to disable rp_filter. See [http://tldp.org/HOWTO/Adv-Routing-HOWTO/lartc.kernel.rpf.html]() for more info on RP filtering. The value of rp_filter files in /proc must be set to zero (ie. "echo 0 > /proc/sys/net/ipv4/conf/all/rp_filter") in order to disable RP filtering. Also, if working on a cloud instance, consider often times these are not configured by default to pass traffic through. These appear popular issues when replicating flow data with tee_transparent feature enabled (that is, packet spoofing);
   5. In case aggregate_filter is in use: the feature expects a libpcap-style filter as value. BPF filters are sensible to both VLAN tags and MPLS labels: if, for example, the traffic is VLAN tagged and the value of aggregate_filter is 'src net X.X.X.X/Y', there will be no match for VLAN-tagged traffic from src net X.X.X.X/Y; the filter should be re-written as 'vlan and src net X.X.X.X/Y'; 6) in case of NetFlow v9/IPFIX collection, two protocols that are template-based, the issue may be with templates not being received by nfacctd (in which case by enabling debug you may see "Discarded NetFlow v9/IPFIX packet (R: unknown template [ .. ]" messages in your logs); you can confirm whether templates are being exported/replicated/received with a touch of "tshark -d udp.port==<NFv9/IPFIX port>,cflow -R cflow.template_id -2"; it may also happen the opposite: templates are received but no data packets are being sent (ie. because sampling is not configured on the actual interfaces on the exporting device): in this case tshark would only show periodic data being received (ie. every 30 secs, 60 secs, etc.) rather than a more constant stream of data.

1. In the case of inconsistent output - inconsistent defined as replaying the same set of data, output produced by the daemon differs - of nfacctd/sfacctd:
  
  1. Check the basics: whether another nfacctd/sfacctd is listening on the very same port; this is legit behaviour due to behaviour of SO_REUSEPORT, in brief: share load among multiple sockets listening on the same port, and SO_REUSEADDR, in brief: don't wait for a closing socket to be closed in order to bind a new
one to the same port, options used on the listening socket;
  2. check all the tips about buffering provided slightly later in this document.

1. Replay packets can be needed, for example, to troubleshoot the behaviour
of one of the pmacct daemons. A capture in libpcap format, suitable for
replay, can be produced with tcpdump. For example to produce a trace for
NetFlow/IPFIX/sFlow this is the command-line: "tcpdump -i <interface> -n -s 0
-w <output file> port <sfacctd/nfacctd listening port>"; for ULOG/NFLOG on
Linux the interface should be in the format "-i nflog:<nflog group>" instead.
For traces over extended periods of time, ie. to troubleshoot specific bogus
packets triggering crashes or capture NetFlow v9/IPFIX templates, optionally
the -G tcpdump option can be specified to rotate the -w output_file each
specified seconds interval (read more on tcpdump man page). Once the trace
has been created, trace file(s) can be replayed by pmacct daemons using the
pcap_savefile (-I) and, optionally, the pcap_savefile_wait (-W) directives,
ie.: "nfacctd -I <pcap savefile> <..>".
For more advanced use-cases, ie. loop indefinitely through the pcap file and
run it with a speed multiplicator in order to stress test the daemon, the
tcpreplay tool can be used. In this case, before replaying NetFlow/IPFIX/sFlow,
L2/L3 of captured packets may need to be adjusted in order to reflect the lab/
replay environment; this can be done with the tcprewrite tool of the tcpreplay
package, ie.: "tcprewrite --enet-smac=<src MAC address> --enet-dmac= <dst MAC
address> -S <src IP address rewrite> -D <dst IP address rewrite> --fixcsum
--infile=<input file, ie. output from tcpdump> --outfile=<output file>". Then
the output file from tcprewrite can be supplied to tcpreplay for the actual
replay to the pmacct daemon, ie.: "tcpreplay -x <speed multiplicator>
-i <output interface> <input file>".

1. Buffering is often an element to tune. While buffering internal to pmacct
(configured with plugin_buffer_size / plugin_pipe_size or plugin_pipe_zmq)
returns warning messages in case of data loss, buffering between pmacct and
the kernel (configured with nfacctd_pipe_size and its equivalents) may be more
tricky to detect and sometimes issues can only be inferred by symptoms (like
sequence number checks for NetFlow v9/IPFIX). For nfacctd and sfacctd daemons,
two commands useful to check this kind of buffering on Linux systems are:
1) "cat /proc/net/udp" or "cat /proc/net/udp6" ensuring that "drops" value
is not increasing and 2) "netstat -s" ensuring, under the section UDP, that
errors are not increasing (since this command returns system-wide counters,
the counter-check would be: stop the pmacct daemon running and, granted the
counter was increasing, verify it does not increase anymore). For pmacctd,
an UNIX signal can be sent to the daemon so that the amount of dropped packets
is reported in the log output (ie. kill -USR1 <pmacctd core PID>).

1. BMP, the BGP Monitoring Protocol, has got drafting traction at IETF. New
protocol features drive the need for inter-op testing. The BMP play tool
( https://github.com/paololucente/bmp_play ) is a simple script to record
and replay raw BMP packets in order to reproduce issues. An example of how
this can be done, here:

  ```
  shell 1> bmp_play.py -m record -p 1790 -f bmp.dump

  shell 1> bmp_play.py -m play -p 1790 -f bmp.dump -d 127.0.0.1

  shell 2> pmbmpd -l 1790 -d -o bmp.log
  ```

  Alternatively, since version 1.7.5, pmbmpd supports pcap_savefile (-I) to replay a pcap trace that includes BMP packets; packets functional to the house-keeping of the TCP session are safely ignored and pcap_filter helps on replay to trash unrelevant (non BMP) packets.
 
1. Packet classification using the nDPI library is among the new features of pmacct 1.7. Following are some tips on how to help by providing meaningful report of issues you may be experiencing in this area. 

  1. Please follow guidelines in the section "Quickstart guide to packet classification" of this document;
  2. Please avoid generic reporting; remember that the most effective way troubleshoot any issue related to packet classification is by the authors being able to reproduce the issue or for them to verify first-hand the issue: whenever possible please share a traffic capture in pcap format or grant remote-access to your testbed;
  3. it is OK to compare classification results achieved with a 3rd party tool also using nDPI for classification; in case of different results, please show the actual results when reporting the issue and please elaborate as much as possible how the comparison was done (ie. say how it is being ensured that the two data-sets are the same or as much as possible similar); 4) excluded from these guidelines are problems related to nDPI but unrelated to classification, ie. memory leaks, performance issues, crashes, etc. for which you can follow the other guide lines in this document in the "Miscellaneous notes and troubleshooting tips" section.

1. If supported and if enabled on the system, the SO_REUSEPORT feature can be
leveraged on Linux and most BSDs where it is part of the standard kernel: it
allows multiple daemons to bind to the same local address and port in order
to load-balance processing of incoming packets. Here a reference to a
presentation of this feature for Linux:

  [https://domsch.com/linux/lpc2010/Scaling_techniques_for_servers_with_high_connection%20rates.pdf]()

  To enable SO_REUSEPORT on a Linux system 'sysctl net.core.allow_reuseport=1'. Also, the processes must be launched by the same user.