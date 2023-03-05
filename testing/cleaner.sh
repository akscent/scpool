#!/bin/bash
# Colors
blue=$'\033[0;34m'
cyan=$'\033[1;96m'
reset=$'\033[0;39m'
green=$'\033[0;32m'
red=$'\033[0;31m'
# Initial total space, used and available
echo "$cyan"'----|Before cleanup|----|'
echo "$blue"'Size  '"$cyan"'|  '"$red"'Used  '"$cyan"'|  '"$green"'Avail '"$cyan"'|'"$reset"
df -h | grep Users | awk -v cyan="$cyan" -v green="$green" -v blue="$blue" -v red="$red" '{print blue $2 " "cyan"=  " red $3 cyan" +  "  green $4 " "cyan"|"}'
echo -n "$reset"
# Cleanup...
rm -rf ~/Library/Application\ Support/Slack/Code\ Cache/ 2>/dev/zero
rm -rf ~/Library/Application\ Support/Slack/Cache/ 2>/dev/zero
rm -rf ~/Library/Application\ Support/Slack/Service\ Worker/CacheStorage/ 2>/dev/zero
### These lines delete all your Visual Code data
#rm -rf ~/Library/ApplicationSupport/CrashReporter/* 2>/dev/zero
#rm -rf ~/Library/Application\ Support/Code/* 2>/dev/zero
#rm -rf ~/Library/Group\ Containers/* 2>/dev/zero
###
rm -rf ~/Library/42_cache/ 2>/dev/zero
rm -rf ~/Library/Caches/CloudKit 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.akd 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.ap.adprivacyd 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.appstore 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.appstoreagent 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.cache_delete 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.commerce 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.iCloudHelper 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.imfoundation.IMRemoteURLConnectionAgent 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.keyboardservicesd 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.nbagent 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.nsservicescache.plist 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.nsurlsessiond 2>/dev/zero
rm -rf ~/Library/Caches/storeassetd 2>/dev/zero
rm -rf ~/Library/Caches/com.microsoft.VSCode.ShipIt 2>/dev/zero
rm -rf ~/Library/Caches/com.microsoft.VSCode 2>/dev/zero
rm -rf ~/Library/Caches/com.google.SoftwareUpdate 2>/dev/zero
rm -rf ~/Library/Caches/com.google.Keystone 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.touristd 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.tiswitcher.cache 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.preferencepanes.usercache 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.preferencepanes.searchindexcache 2>/dev/zero
rm -rf ~/Library/Caches/com.apple.parsecd 2>/dev/zero
rm -rf ~/Library/Caches/ 2>/dev/zero
rm -rf ~/.Trash/* 2>/dev/zero
rm -rf ~/.kube/cache/* 2>/dev/zero
rm -rf ~/Library/Containers/com.docker.docker/Data/vms/* 2>/dev/zero
rm -rf ~/Library/Application\ Support/Firefox/Profiles/hdsrd79k.default-release/storage 2>/dev/zero
rm -rf ~/Library/42_cache 2>/dev/zero
rm -rf ~/Library/Application\ Support/Code/User/workspaceStorage 2>/dev/zero
rm -rf ~//Library/Application\ Support/Spotify/PersistentCache 2>/dev/zero
rm -rf ~/Library/Application\ Support/Telegram\ Desktop/tdata/user_data 2>/dev/zero
rm -rf ~/Library/Application\ Support/Telegram\ Desktop/tdata/emoji 2>/dev/zero
rm -rf ~/Library/Application\ Support/Code/Cache/Library/Application\ Support/Code/Cachei 2>/dev/zero
rm -rf ~/Library/Application\ Support/Code/CacheData 2>/dev/zero
rm -rf ~/Library/Application\ Support/Code/Cache 2>/dev/zero
rm -rf ~Library/Application\ Support/Code/Crashpad/completed 2>/dev/zero
rm -rf ~/Library/Caches/* 2>/dev/zero
rm -rf ~/Library/Application\ Support/Slack/Cache/* 2>/dev/zero
rm -rf ~/Library/Application\ Support/Slack/Service\ Worker/CacheStorage/* 2>/dev/zero
rm -rf ~/Library/Group\ Containers/6N38VWS5BX.ru.keepcoder.Telegram/account-570841890615083515/postbox/* 2>/dev/zero
rm -rf ~/Library/Caches 2>/dev/zero
rm -rf ~/Library/Application\ Support/Code/CachedData 2>/dev/zero
rm -rf ~/Library/Application\ Support/Code/CachedExtension 2>/dev/zero
rm -rf ~/Library/Application\ Support/Code/CachedExtensions 2>/dev/zero
rm -rf ~/Library/Application\ Support/Code/CachedExtensionVSIXs 2>/dev/zero
rm -rf ~/Library/Application\ Support/Code/Code\ Cache 2>/dev/zero
rm -rf ~/Library/Application\ Support/Slack/Cache 2>/dev/zero
rm -rf ~/Library/Application\ Support/Slack/Code\ Cache 2>/dev/zero
rm -rf ~/Library/Application\ Support/Slack/Service\ Worker/CacheStorage 2>/dev/zero
rm -rf ~/Library/Application\ Support/Slack/Cache/* -y 2>/dev/zero
rm -rf ~/Library/Application\ Support/Slack/Service\ Worker/CacheStorage/* -y 2>/dev/zero
rm -rf ~/Library/Application\ Support/Google/Chrome/Default/Service\ Worker/CacheStorage/* 2>/dev/zero
rm -rf ~/Library/Application\ Support/Google/Chrome/Crashpad/completed/* 2>/dev/zero
rm -rf ~/Library/Caches/* -y 2>/dev/zero
rm -rf ~/.Trash/* -y 2>/dev/zero
rm -rf ~/Library/Safari/* -y 2>/dev/zero
rm -rf ~/.kube/cache/* -y 2>/dev/zero
rm -rf ~/Library/Application\ Support/Code/CachedData/* -y 2>/dev/zero
rm -rf ~/Library/Application\ Support/Code/Crashpad/completed/* -y 2>/dev/zero
rm -rf ~/Library/Application\ Support/Code/User/workspaceStoratge/* -y 2>/dev/zero
rm -rf ~/Library/Containers/com.docker.docker/Data/vms/* -y 2>/dev/zero
rm -rf ~/Library/Containers/com.apple.Safari/Data/Library/Caches/* -y 2>/dev/zero
rm -rf ~/Library/Containers/org.telegram.desktop/Data/Library/Application\ Support/Telegram\ Desktop/tdata/emoji/* -y 2>/dev/zero
# Space after cleanup
echo "$cyan"'----|After  cleanup|----|'
echo "$blue"'Size  '"$cyan"'|  '"$red"'Used  '"$cyan"'|  '"$green"'Avail '"$cyan"'|'"$reset"
df -h | grep Users | awk -v cyan="$cyan" -v green="$green" -v blue="$blue" -v red="$red" '{print blue $2 " "cyan"=  " red $3 cyan" +  "  green $4 " "cyan"|"}'
echo -n "$reset"
echo "$cyan"'----|Cleanup  ended|----|'
