


ssh aknue@lxplus.cern.ch "cern-get-sso-cookie -u https://bigpanda.cern.ch/ -o bigpanda.cookie.txt;"
ssh aknue@lxplus.cern.ch 'curl -b ~/bigpanda.cookie.txt -H '"'"'Accept: application/json'"'"' -H '"'"'Content-Type: application/json'"'"' "https://bigpanda.cern.ch/tasks/?taskname=user.aknue*s3126*21258_V1*&days=10&json"'