./selenika-peer-server \
--ssl_srt=/home/qqq/projectx/selenika/selenika_service_core_lib/tests/ssl-certificates/server.crt \
--ssl_key=/home/qqq/projectx/selenika/selenika_service_core_lib/tests/ssl-certificates/server.key \
--server=localhost --port=8080 \
--max_num_connections=10 \
--dbg_level=debug \
--run_as_service=false \
--log=/var/log/selenika-peer-server.log