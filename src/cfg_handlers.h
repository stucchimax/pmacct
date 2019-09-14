/*
    pmacct (Promiscuous mode IP Accounting package)
    pmacct is Copyright (C) 2003-2019 by Paolo Lucente
*/

/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if no, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef CFG_HANDLER_H
#define CFG_HANDLER_H

/* prototypes */
extern int parse_truefalse(char *);
extern int parse_truefalse_nonzero(char *);
extern int validate_truefalse(int);
extern void cfg_key_legacy_warning(char *, char *);

extern int cfg_key_debug(char *, char *, char *);
extern int cfg_key_debug_internal_msg(char *, char *, char *);
extern int cfg_key_syslog(char *, char *, char *);
extern int cfg_key_logfile(char *, char *, char *);
extern int cfg_key_pidfile(char *, char *, char *);
extern int cfg_key_daemonize(char *, char *, char *);
extern int cfg_key_proc_name(char *, char *, char *);
extern int cfg_key_proc_priority(char *, char *, char *);
extern int cfg_key_aggregate(char *, char *, char *);
extern int cfg_key_aggregate_primitives(char *, char *, char *);
extern int cfg_key_snaplen(char *, char *, char *);
extern int cfg_key_aggregate_filter(char *, char *, char *);
extern int cfg_key_pcap_filter(char *, char *, char *);
extern int cfg_key_pcap_protocol(char *, char *, char *);
extern int cfg_key_pcap_savefile(char *, char *, char *);
extern int cfg_key_pcap_savefile_wait(char *, char *, char *);
extern int cfg_key_pcap_savefile_delay(char *, char *, char *);
extern int cfg_key_pcap_savefile_replay(char *, char *, char *);
extern int cfg_key_pcap_direction(char *, char *, char *);
extern int cfg_key_pcap_ifindex(char *, char *, char *);
extern int cfg_key_pcap_interfaces_map(char *, char *, char *);
extern int cfg_key_use_ip_next_hop(char *, char *, char *);
extern int cfg_key_decode_arista_trailer(char *, char *, char *);
extern int cfg_key_thread_stack(char *, char *, char *);
extern int cfg_key_pcap_interface(char *, char *, char *);
extern int cfg_key_pcap_interface_wait(char *, char *, char *);
extern int cfg_key_files_umask(char *, char *, char *);
extern int cfg_key_files_uid(char *, char *, char *);
extern int cfg_key_files_gid(char *, char *, char *);
extern int cfg_key_promisc(char *, char *, char *);
extern int cfg_key_num_protos(char *, char *, char *);
extern int cfg_key_num_hosts(char *, char *, char *);
extern int cfg_key_imt_path(char *, char *, char *);
extern int cfg_key_imt_passwd(char *, char *, char *);
extern int cfg_key_imt_buckets(char *, char *, char *);
extern int cfg_key_imt_mem_pools_number(char *, char *, char *);
extern int cfg_key_imt_mem_pools_size(char *, char *, char *);
extern int cfg_key_sql_db(char *, char *, char *);
extern int cfg_key_sql_table(char *, char *, char *);
extern int cfg_key_sql_table_schema(char *, char *, char *);
extern int cfg_key_sql_table_version(char *, char *, char *);
extern int cfg_key_sql_table_type(char *, char *, char *);
extern int cfg_key_sql_conn_ca_file(char *, char *, char *);
extern int cfg_key_sql_host(char *, char *, char *);
extern int cfg_key_sql_port(char *, char *, char *);
extern int cfg_key_sql_data(char *, char *, char *);
extern int cfg_key_sql_user(char *, char *, char *);
extern int cfg_key_sql_passwd(char *, char *, char *);
extern int cfg_key_sql_refresh_time(char *, char *, char *);
extern int cfg_key_sql_startup_delay(char *, char *, char *);
extern int cfg_key_sql_optimize_clauses(char *, char *, char *);
extern int cfg_key_sql_history(char *, char *, char *);
extern int cfg_key_sql_history_offset(char *, char *, char *);
extern int cfg_key_sql_history_roundoff(char *, char *, char *);
extern int cfg_key_sql_recovery_backup_host(char *, char *, char *);
extern int cfg_key_sql_trigger_exec(char *, char *, char *);
extern int cfg_key_sql_trigger_time(char *, char *, char *);
extern int cfg_key_sql_cache_entries(char *, char *, char *);
extern int cfg_key_sql_dont_try_update(char *, char *, char *);
extern int cfg_key_sql_preprocess(char *, char *, char *);
extern int cfg_key_sql_preprocess_type(char *, char *, char *);
extern int cfg_key_sql_multi_values(char *, char *, char *);
extern int cfg_key_sql_locking_style(char *, char *, char *);
extern int cfg_key_sql_use_copy(char *, char *, char *);
extern int cfg_key_sql_delimiter(char *, char *, char *);
extern int cfg_key_timestamps_rfc3339(char *, char *, char *);
extern int cfg_key_timestamps_utc(char *, char *, char *);
extern int cfg_key_timestamps_secs(char *, char *, char *);
extern int cfg_key_timestamps_since_epoch(char *, char *, char *);
extern int cfg_key_mongo_insert_batch(char *, char *, char *);
extern int cfg_key_message_broker_output(char *, char *, char *);
extern int cfg_key_avro_buffer_size(char *, char *, char *);
extern int cfg_key_avro_schema_file(char *, char *, char *);
extern int cfg_key_amqp_exchange_type(char *, char *, char *);
extern int cfg_key_amqp_persistent_msg(char *, char *, char *);
extern int cfg_key_amqp_frame_max(char *, char *, char *);
extern int cfg_key_amqp_heartbeat_interval(char *, char *, char *);
extern int cfg_key_amqp_vhost(char *, char *, char *);
extern int cfg_key_amqp_routing_key_rr(char *, char *, char *);
extern int cfg_key_amqp_avro_schema_routing_key(char *, char *, char *);
extern int cfg_key_amqp_avro_schema_refresh_time(char *, char *, char *);
extern int cfg_key_kafka_broker_port(char *, char *, char *);
extern int cfg_key_kafka_partition(char *, char *, char *);
extern int cfg_key_kafka_partition_dynamic(char *, char *, char *);
extern int cfg_key_kafka_partition_key(char *, char *, char *);
extern int cfg_key_kafka_avro_schema_topic(char *, char *, char *);
extern int cfg_key_kafka_avro_schema_refresh_time(char *, char *, char *);
extern int cfg_key_kafka_avro_schema_registry(char *, char *, char *);
extern int cfg_key_kafka_config_file(char *, char *, char *);
extern int cfg_key_plugin_pipe_size(char *, char *, char *);
extern int cfg_key_plugin_buffer_size(char *, char *, char *);
extern int cfg_key_plugin_pipe_zmq(char *, char *, char *);
extern int cfg_key_plugin_pipe_zmq_retry(char *, char *, char *);
extern int cfg_key_plugin_pipe_zmq_profile(char *, char *, char *);
extern int cfg_key_plugin_pipe_zmq_hwm(char *, char *, char *);
extern int cfg_key_plugin_exit_any(char *, char *, char *);
extern int cfg_key_networks_mask(char *, char *, char *);
extern int cfg_key_networks_file(char *, char *, char *);
extern int cfg_key_networks_file_filter(char *, char *, char *);
extern int cfg_key_networks_file_no_lpm(char *, char *, char *);
extern int cfg_key_networks_no_mask_if_zero(char *, char *, char *);
extern int cfg_key_networks_cache_entries(char *, char *, char *);
extern int cfg_key_ports_file(char *, char *, char *);
extern int cfg_key_print_cache_entries(char *, char *, char *);
extern int cfg_key_print_markers(char *, char *, char *);
extern int cfg_key_print_output(char *, char *, char *);
extern int cfg_key_print_output_file(char *, char *, char *);
extern int cfg_key_print_output_file_append(char *, char *, char *);
extern int cfg_key_print_output_lock_file(char *, char *, char *);
extern int cfg_key_print_output_separator(char *, char *, char *);
extern int cfg_key_print_output_custom_lib(char *, char *, char *);
extern int cfg_key_print_output_custom_cfg_file(char *, char *, char *);
extern int cfg_key_print_latest_file(char *, char *, char *);
extern int cfg_key_nfacctd_port(char *, char *, char *);
extern int cfg_key_nfacctd_ip(char *, char *, char *);
extern int cfg_key_nfacctd_allow_file(char *, char *, char *);
extern int cfg_key_nfacctd_time_secs(char *, char *, char *);
extern int cfg_key_nfacctd_time_new(char *, char *, char *);
extern int cfg_key_nfacctd_as_new(char *, char *, char *);
extern int cfg_key_nfacctd_net(char *, char *, char *);
extern int cfg_key_nfacctd_disable_checks(char *, char *, char *);
extern int cfg_key_nfacctd_disable_opt_scope_check(char *, char *, char *);
extern int cfg_key_nfacctd_mcast_groups(char *, char *, char *);
extern int cfg_key_nfacctd_pipe_size(char *, char *, char *);
extern int cfg_key_nfacctd_pro_rating(char *, char *, char *);
extern int cfg_key_nfacctd_templates_file(char *, char *, char *);
extern int cfg_key_nfacctd_account_options(char *, char *, char *);
extern int cfg_key_nfacctd_stitching(char *, char *, char *);
extern int cfg_key_nfacctd_kafka_broker_host(char *, char *, char *);
extern int cfg_key_nfacctd_kafka_broker_port(char *, char *, char *);
extern int cfg_key_nfacctd_kafka_topic(char *, char *, char *);
extern int cfg_key_nfacctd_kafka_config_file(char *, char *, char *);
extern int cfg_key_nfacctd_zmq_address(char *, char *, char *);
extern int cfg_key_pmacctd_force_frag_handling(char *, char *, char *);
extern int cfg_key_pmacctd_frag_buffer_size(char *, char *, char *);
extern int cfg_key_pmacctd_flow_buffer_size(char *, char *, char *);
extern int cfg_key_pmacctd_flow_buffer_buckets(char *, char *, char *);
extern int cfg_key_pmacctd_conntrack_buffer_size(char *, char *, char *);
extern int cfg_key_pmacctd_flow_lifetime(char *, char *, char *);
extern int cfg_key_pmacctd_flow_tcp_lifetime(char *, char *, char *);
extern int cfg_key_pmacctd_ext_sampling_rate(char *, char *, char *);
extern int cfg_key_pmacctd_nonroot(char *, char *, char *);
extern int cfg_key_sfacctd_renormalize(char *, char *, char *);
extern int cfg_key_sfacctd_counter_output(char *, char *, char *);
extern int cfg_key_sfacctd_counter_file(char *, char *, char *);
extern int cfg_key_sfacctd_counter_amqp_host(char *, char *, char *);
extern int cfg_key_sfacctd_counter_amqp_vhost(char *, char *, char *);
extern int cfg_key_sfacctd_counter_amqp_user(char *, char *, char *);
extern int cfg_key_sfacctd_counter_amqp_passwd(char *, char *, char *);
extern int cfg_key_sfacctd_counter_amqp_exchange(char *, char *, char *);
extern int cfg_key_sfacctd_counter_amqp_exchange_type(char *, char *, char *);
extern int cfg_key_sfacctd_counter_amqp_routing_key(char *, char *, char *);
extern int cfg_key_sfacctd_counter_amqp_persistent_msg(char *, char *, char *);
extern int cfg_key_sfacctd_counter_amqp_frame_max(char *, char *, char *);
extern int cfg_key_sfacctd_counter_amqp_heartbeat_interval(char *, char *, char *);
extern int cfg_key_sfacctd_counter_amqp_retry(char *, char *, char *);
extern int cfg_key_sfacctd_counter_kafka_broker_host(char *, char *, char *);
extern int cfg_key_sfacctd_counter_kafka_broker_port(char *, char *, char *);
extern int cfg_key_sfacctd_counter_kafka_topic(char *, char *, char *);
extern int cfg_key_sfacctd_counter_kafka_partition(char *, char *, char *);
extern int cfg_key_sfacctd_counter_kafka_partition_key(char *, char *, char *);
extern int cfg_key_sfacctd_counter_kafka_retry(char *, char *, char *);
extern int cfg_key_sfacctd_counter_kafka_config_file(char *, char *, char *);
extern int cfg_key_telemetry_daemon(char *, char *, char *);
extern int cfg_key_telemetry_port_tcp(char *, char *, char *);
extern int cfg_key_telemetry_port_udp(char *, char *, char *);
extern int cfg_key_telemetry_ip(char *, char *, char *);
extern int cfg_key_telemetry_zmq_address(char *, char *, char *);
extern int cfg_key_telemetry_decoder(char *, char *, char *);
extern int cfg_key_telemetry_max_peers(char *, char *, char *);
extern int cfg_key_telemetry_peer_timeout(char *, char *, char *);
extern int cfg_key_telemetry_allow_file(char *, char *, char *);
extern int cfg_key_telemetry_pipe_size(char *, char *, char *);
extern int cfg_key_telemetry_ip_precedence(char *, char *, char *);
extern int cfg_key_telemetry_msglog_output(char *, char *, char *);
extern int cfg_key_telemetry_msglog_file(char *, char *, char *);
extern int cfg_key_telemetry_msglog_amqp_host(char *, char *, char *);
extern int cfg_key_telemetry_msglog_amqp_vhost(char *, char *, char *);
extern int cfg_key_telemetry_msglog_amqp_user(char *, char *, char *);
extern int cfg_key_telemetry_msglog_amqp_passwd(char *, char *, char *);
extern int cfg_key_telemetry_msglog_amqp_exchange(char *, char *, char *);
extern int cfg_key_telemetry_msglog_amqp_exchange_type(char *, char *, char *);
extern int cfg_key_telemetry_msglog_amqp_routing_key(char *, char *, char *);
extern int cfg_key_telemetry_msglog_amqp_routing_key_rr(char *, char *, char *);
extern int cfg_key_telemetry_msglog_amqp_persistent_msg(char *, char *, char *);
extern int cfg_key_telemetry_msglog_amqp_frame_max(char *, char *, char *);
extern int cfg_key_telemetry_msglog_amqp_heartbeat_interval(char *, char *, char *);
extern int cfg_key_telemetry_msglog_amqp_retry(char *, char *, char *);
extern int cfg_key_telemetry_msglog_kafka_broker_host(char *, char *, char *);
extern int cfg_key_telemetry_msglog_kafka_broker_port(char *, char *, char *);
extern int cfg_key_telemetry_msglog_kafka_topic(char *, char *, char *);
extern int cfg_key_telemetry_msglog_kafka_topic_rr(char *, char *, char *);
extern int cfg_key_telemetry_msglog_kafka_partition(char *, char *, char *);
extern int cfg_key_telemetry_msglog_kafka_partition_key(char *, char *, char *);
extern int cfg_key_telemetry_msglog_kafka_retry(char *, char *, char *);
extern int cfg_key_telemetry_msglog_kafka_config_file(char *, char *, char *);
extern int cfg_key_telemetry_dump_output(char *, char *, char *);
extern int cfg_key_telemetry_dump_file(char *, char *, char *);
extern int cfg_key_telemetry_dump_latest_file(char *, char *, char *);
extern int cfg_key_telemetry_dump_refresh_time(char *, char *, char *);
extern int cfg_key_telemetry_dump_amqp_host(char *, char *, char *);
extern int cfg_key_telemetry_dump_amqp_vhost(char *, char *, char *);
extern int cfg_key_telemetry_dump_amqp_user(char *, char *, char *);
extern int cfg_key_telemetry_dump_amqp_passwd(char *, char *, char *);
extern int cfg_key_telemetry_dump_amqp_exchange(char *, char *, char *);
extern int cfg_key_telemetry_dump_amqp_exchange_type(char *, char *, char *);
extern int cfg_key_telemetry_dump_amqp_routing_key(char *, char *, char *);
extern int cfg_key_telemetry_dump_amqp_routing_key_rr(char *, char *, char *);
extern int cfg_key_telemetry_dump_amqp_persistent_msg(char *, char *, char *);
extern int cfg_key_telemetry_dump_amqp_frame_max(char *, char *, char *);
extern int cfg_key_telemetry_dump_amqp_heartbeat_interval(char *, char *, char *);
extern int cfg_key_telemetry_dump_kafka_broker_host(char *, char *, char *);
extern int cfg_key_telemetry_dump_kafka_broker_port(char *, char *, char *);
extern int cfg_key_telemetry_dump_kafka_topic(char *, char *, char *);
extern int cfg_key_telemetry_dump_kafka_topic_rr(char *, char *, char *);
extern int cfg_key_telemetry_dump_kafka_partition(char *, char *, char *);
extern int cfg_key_telemetry_dump_kafka_partition_key(char *, char *, char *);
extern int cfg_key_telemetry_dump_kafka_config_file(char *, char *, char *);
extern int cfg_key_maps_refresh(char *, char *, char *);
extern int cfg_key_maps_index(char *, char *, char *);
extern int cfg_key_maps_entries(char *, char *, char *);
extern int cfg_key_maps_row_len(char *, char *, char *);
extern int cfg_key_pre_tag_map(char *, char *, char *);
extern int cfg_key_pre_tag_filter(char *, char *, char *);
extern int cfg_key_pre_tag2_filter(char *, char *, char *);
extern int cfg_key_pre_tag_label_filter(char *, char *, char *);
extern int cfg_key_post_tag(char *, char *, char *);
extern int cfg_key_post_tag2(char *, char *, char *);
extern int cfg_key_sampling_rate(char *, char *, char *);
extern int cfg_key_sampling_map(char *, char *, char *);
extern int cfg_key_classifiers(char *, char *, char *);
extern int cfg_key_classifier_tentatives(char *, char *, char *);
extern int cfg_key_classifier_table_num(char *, char *, char *);
extern int cfg_key_classifier_ndpi_num_roots(char *, char *, char *);
extern int cfg_key_classifier_ndpi_max_flows(char *, char *, char *);
extern int cfg_key_classifier_ndpi_proto_guess(char *, char *, char *);
extern int cfg_key_classifier_ndpi_idle_scan_period(char *, char *, char *);
extern int cfg_key_classifier_ndpi_idle_max_time(char *, char *, char *);
extern int cfg_key_classifier_ndpi_idle_scan_budget(char *, char *, char *);
extern int cfg_key_classifier_ndpi_giveup_proto_tcp(char *, char *, char *);
extern int cfg_key_classifier_ndpi_giveup_proto_udp(char *, char *, char *);
extern int cfg_key_classifier_ndpi_giveup_proto_other(char *, char *, char *);
extern int cfg_key_nfprobe_timeouts(char *, char *, char *);
extern int cfg_key_nfprobe_hoplimit(char *, char *, char *);
extern int cfg_key_nfprobe_maxflows(char *, char *, char *);
extern int cfg_key_nfprobe_receiver(char *, char *, char *);
extern int cfg_key_nfprobe_version(char *, char *, char *);
extern int cfg_key_nfprobe_engine(char *, char *, char *);
extern int cfg_key_nfprobe_peer_as(char *, char *, char *);
extern int cfg_key_nfprobe_source_ip(char *, char *, char *);
extern int cfg_key_nfprobe_ip_precedence(char *, char *, char *);
extern int cfg_key_nfprobe_direction(char *, char *, char *);
extern int cfg_key_nfprobe_ifindex(char *, char *, char *);
extern int cfg_key_nfprobe_ifindex_override(char *, char *, char *);
extern int cfg_key_nfprobe_dont_cache(char *, char *, char *);
extern int cfg_key_sfprobe_receiver(char *, char *, char *);
extern int cfg_key_sfprobe_agentip(char *, char *, char *);
extern int cfg_key_sfprobe_agentsubid(char *, char *, char *);
extern int cfg_key_sfprobe_ifspeed(char *, char *, char *);
extern int cfg_key_tee_receivers(char *, char *, char *);
extern int cfg_key_tee_transparent(char *, char *, char *);
extern int cfg_key_tee_max_receivers(char *, char *, char *);
extern int cfg_key_tee_max_receiver_pools(char *, char *, char *);
extern int cfg_key_tee_pipe_size(char *, char *, char *);
extern int cfg_key_tee_kafka_config_file(char *, char *, char *);
extern int cfg_key_nfacctd_bgp(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_output(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_file(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_avro_schema_file(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_amqp_host(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_amqp_vhost(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_amqp_user(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_amqp_passwd(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_amqp_exchange(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_amqp_exchange_type(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_amqp_routing_key(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_amqp_routing_key_rr(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_amqp_persistent_msg(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_amqp_frame_max(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_amqp_heartbeat_interval(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_amqp_retry(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_kafka_broker_host(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_kafka_broker_port(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_kafka_topic(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_kafka_topic_rr(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_kafka_partition(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_kafka_partition_key(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_kafka_retry(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_kafka_config_file(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_msglog_kafka_avro_schema_registry(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_max_peers(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_ip(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_id(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_as(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_port(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_ip_precedence(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_allow_file(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_aspath_radius(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_stdcomm_pattern(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_extcomm_pattern(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_lrgcomm_pattern(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_stdcomm_pattern_to_asn(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_lrgcomm_pattern_to_asn(char *, char *, char *);
extern int cfg_key_bgp_blackhole_stdcomm_list(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_peer_src_as_type(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_src_std_comm_type(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_src_ext_comm_type(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_src_lrg_comm_type(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_src_as_path_type(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_src_local_pref_type(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_src_med_type(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_src_roa_type(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_peer_as_skip_subas(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_peer_src_as_map(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_src_local_pref_map(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_src_med_map(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_to_agent_map(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_follow_default(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_follow_nexthop(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_follow_nexthop_external(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_disable_router_id_check(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_neighbors_file(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_md5_file(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_peer_buckets(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_per_peer_buckets(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_attr_hash_buckets(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_per_peer_hash(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_output(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_file(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_latest_file(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_avro_schema_file(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_refresh_time(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_amqp_host(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_amqp_vhost(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_amqp_user(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_amqp_passwd(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_amqp_exchange(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_amqp_exchange_type(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_amqp_routing_key(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_amqp_routing_key_rr(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_amqp_persistent_msg(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_amqp_frame_max(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_amqp_heartbeat_interval(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_kafka_broker_host(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_kafka_broker_port(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_kafka_topic(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_kafka_topic_rr(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_kafka_partition(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_kafka_partition_key(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_kafka_config_file(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_table_dump_kafka_avro_schema_registry(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_batch(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_batch_interval(char *, char *, char *);
extern int cfg_key_nfacctd_bgp_pipe_size(char *, char *, char *);
extern int cfg_key_bgp_lg(char *, char *, char *);
extern int cfg_key_bgp_lg_ip(char *, char *, char *);
extern int cfg_key_bgp_lg_port(char *, char *, char *);
extern int cfg_key_bgp_lg_threads(char *, char *, char *);
extern int cfg_key_bgp_lg_user(char *, char *, char *);
extern int cfg_key_bgp_lg_passwd(char *, char *, char *);
extern int cfg_key_bgp_xconnect_map(char *, char *, char *);
extern int cfg_key_nfacctd_bmp(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_ip(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_port(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_pipe_size(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_max_peers(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_allow_file(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_ip_precedence(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_batch(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_batch_interval(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_output(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_file(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_avro_schema_file(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_amqp_host(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_amqp_vhost(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_amqp_user(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_amqp_passwd(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_amqp_exchange(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_amqp_exchange_type(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_amqp_routing_key(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_amqp_routing_key_rr(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_amqp_persistent_msg(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_amqp_frame_max(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_amqp_heartbeat_interval(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_amqp_retry(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_kafka_broker_host(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_kafka_broker_port(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_kafka_topic(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_kafka_topic_rr(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_kafka_partition(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_kafka_partition_key(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_kafka_retry(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_kafka_config_file(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_msglog_kafka_avro_schema_registry(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_table_peer_buckets(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_table_per_peer_buckets(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_table_attr_hash_buckets(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_table_per_peer_hash(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_output(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_file(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_avro_schema_file(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_latest_file(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_refresh_time(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_amqp_host(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_amqp_vhost(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_amqp_user(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_amqp_passwd(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_amqp_exchange(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_amqp_exchange_type(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_amqp_routing_key(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_amqp_routing_key_rr(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_amqp_persistent_msg(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_amqp_frame_max(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_amqp_heartbeat_interval(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_kafka_broker_host(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_kafka_broker_port(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_kafka_topic(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_kafka_topic_rr(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_kafka_partition(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_kafka_partition_key(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_kafka_config_file(char *, char *, char *);
extern int cfg_key_nfacctd_bmp_dump_kafka_avro_schema_registry(char *, char *, char *);
extern int cfg_key_nfacctd_flow_to_rd_map(char *, char *, char *);
extern int cfg_key_nfacctd_isis(char *, char *, char *);
extern int cfg_key_nfacctd_isis_ip(char *, char *, char *);
extern int cfg_key_nfacctd_isis_net(char *, char *, char *);
extern int cfg_key_nfacctd_isis_iface(char *, char *, char *);
extern int cfg_key_nfacctd_isis_mtu(char *, char *, char *);
extern int cfg_key_nfacctd_isis_msglog(char *, char *, char *);
extern int cfg_key_rpki_roas_file(char *, char *, char *);
extern int cfg_key_rpki_rtr_cache(char *, char *, char *);
extern int cfg_key_rpki_rtr_cache_version(char *, char *, char *);
extern int cfg_key_rpki_rtr_cache_pipe_size(char *, char *, char *);
extern int cfg_key_rpki_rtr_cache_ip_precedence(char *, char *, char *);
extern int cfg_key_igp_daemon_map(char *, char *, char *);
extern int cfg_key_igp_daemon_map_msglog(char *, char *, char *);
extern int cfg_key_geoip_ipv4_file(char *, char *, char *);
extern int cfg_key_geoip_ipv6_file(char *, char *, char *);
extern int cfg_key_geoipv2_file(char *, char *, char *);
extern int cfg_key_uacctd_group(char *, char *, char *);
extern int cfg_key_uacctd_nl_size(char *, char *, char *);
extern int cfg_key_uacctd_threshold(char *, char *, char *);
extern int cfg_key_tunnel_0(char *, char *, char *);
extern int cfg_key_dump_max_writers(char *, char *, char *);
extern int cfg_key_tmp_asa_bi_flow(char *, char *, char *);
extern int cfg_key_tmp_bgp_lookup_compare_ports(char *, char *, char *);

extern void parse_time(char *, char *, int *, int *);
extern void cfg_set_aggregate(char *, u_int64_t [], u_int64_t, char *);

#endif //CFG_HANDLER_H
