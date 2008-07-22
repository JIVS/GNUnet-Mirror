; @brief Installer script for Windows
; @author Nils Durner

; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "GNUnet"
!define PRODUCT_VERSION "0.8.0a"
!define PRODUCT_PUBLISHER "GNU"
!define PRODUCT_WEB_SITE "http://www.gnunet.org/"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"

SetCompressor lzma

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\nsis1-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\nsis1-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "License.rtf"
; Components page
!insertmacro MUI_PAGE_COMPONENTS
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Start menu page
var ICONS_GROUP
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "GNUnet"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\README"
!define MUI_FINISHPAGE_SHOWREADME_FUNCTION "ShowReadme"
!define MUI_FINISHPAGE_RUN
!define MUI_FINISHPAGE_RUN_TEXT "GNUnet Setup"
!define MUI_FINISHPAGE_RUN_FUNCTION "LaunchSetup"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "German"

; Reserve files
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

; MUI end ------

; Non-standard texts
LangString deleteall ${LANG_ENGLISH} "Do you also want to delete all GNUnet configuration files and databases?"
LangString deleteall ${LANG_GERMAN} "M�chten Sie au�erdem alle GNUnet Konfigurationsdateien und Datenbanken l�schen?"
LangString confwizard ${LANG_ENGLISH} "GNUnet Configuration Wizard"
LangString confwizard ${LANG_GERMAN} "GNUnet Konfigurationsassistent"
LangString gnunetdconfig ${LANG_ENGLISH} "GNUnet Server configuration"
LangString gnunetdconfig ${LANG_GERMAN} "GNUnet Server Konfiguration"
LangString gnunetclientconfig ${LANG_ENGLISH} "GNUnet Client configuration"
LangString gnunetclientconfig ${LANG_GERMAN} "GNUnet Client Konfiguration"

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\GNU\GNUnet"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Var LANGCODE
Var USR_PROF
Var DIRLEN
Var DATADIR

InstType "User"
InstType "GNUnet Server"
InstType "GNUnet Client"
InstType "Everything"

Function LaunchSetup
  ExecShell "" "$SMPROGRAMS\$ICONS_GROUP\$(confwizard).lnk"
FunctionEnd

SetOverwrite ifnewer

SectionGroup "GNUnet" SEC_GNUNET
	Section "Base" SEC_GNUNET_BASE
		SectionIn RO
	  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP"
	  
	  SetOutPath "$INSTDIR"
	  File "C:\GNUnet\AUTHORS"
	  File "C:\GNUnet\ChangeLog"
	  File "C:\GNUnet\COPYING"
	  File "C:\GNUnet\PLATFORMS"
	  File "C:\GNUnet\README"
	  File "C:\GNUnet\UPDATING"
	  
	  SetOutPath "$INSTDIR\bin"
	  File "gnu.ico"	
	  File "config.ico"	

		File "C:\GNUnet\bin\libgnunetmodule_state.dll" 
		File "C:\GNUnet\bin\libgnunetutil-3.dll" 
		; FS base?
		File "C:\GNUnet\bin\libgnunetecrs_core-0.dll"
    File "C:\GNUnet\bin\libgnunetgetoption_api-0.dll"
    ; Fixme: client only
    File "C:\GNUnet\bin\libgnunettraffic_api-0.dll"
		File "C:\GNUnet\bin\gnunet-win-tool.exe"
		File "C:\GNUnet\bin\gnunet-update.exe" 
    
    SetOutPath "$INSTDIR\share\plibc"
    File "C:\GNUnet\share\plibc\plibc.ini"
    
		SetOutPath "$INSTDIR\var\lib\GNUnet"
    SetOutPath "$INSTDIR\var\run"
		SetOutPath "$INSTDIR\tmp"
		
	  SetOutPath "$INSTDIR\bin"
	  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\GNUnet.lnk" "$INSTDIR\bin\gnunet-qt.exe" "" "$INSTDIR\bin\gnu.ico"
	  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\$(confwizard).lnk" "$INSTDIR\bin\gnunet-setup.exe" "-d wizard-qt" "$INSTDIR\bin\config.ico"
    Delete "$SMPROGRAMS\$ICONS_GROUP\$(gnunetdconfig).lnk"
    Delete $SMPROGRAMS\$ICONS_GROUP\$(gnunetclientconfig).lnk"
;	  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\$(gnunetdconfig).lnk" "$INSTDIR\bin\gnunet-setup.exe" "-d gconfig" "$INSTDIR\bin\config.ico"
;	  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\$(gnunetclientconfig).lnk" "$INSTDIR\bin\gnunet-setup.exe" "gconfig" "$INSTDIR\bin\config.ico"
	  CreateShortCut "$DESKTOP\GNUnet.lnk" "$INSTDIR\bin\gnunet-qt.exe" "" "$INSTDIR\bin\gnu.ico"
	SectionEnd
	
	SectionGroup "Language Support" SEC_LANG
		Section "German" SEC_LANG_DE
			SectionIn 1 2 3 4
		  SetOutPath "$INSTDIR\share\locale\de\LC_MESSAGES"
			File "C:\GNUnet\share\locale\de\LC_MESSAGES\GNUnet.mo" 
			File "C:\GNUnet\share\locale\de\LC_MESSAGES\libextractor.mo" 
		SectionEnd
		Section "Kinyarwanda" SEC_LANG_RW
			SectionIn 1 2 3 4
		  SetOutPath "$INSTDIR\share\locale\rw\LC_MESSAGES"
			File "C:\GNUnet\share\locale\rw\LC_MESSAGES\GNUnet.mo" 
			File "C:\GNUnet\share\locale\rw\LC_MESSAGES\libextractor.mo" 
		SectionEnd
		Section "Spanish" SEC_LANG_ES
			SectionIn 1 2 3 4
		  SetOutPath "$INSTDIR\share\locale\es\LC_MESSAGES"
			File "C:\GNUnet\share\locale\es\LC_MESSAGES\GNUnet.mo" 
		SectionEnd
    Section "Swedish" SEC_LANG_SV
      SectionIn 1 2 3 4
      SetOutPath "$INSTDIR\share\locale\sv\LC_MESSAGES"
      File "C:\GNUnet\share\locale\sv\LC_MESSAGES\GNUnet.mo" 
      File "C:\GNUnet\share\locale\sv\LC_MESSAGES\libextractor.mo" 
    SectionEnd
		Section "Vietnamese" SEC_LANG_VI
			SectionIn 1 2 3 4
		  SetOutPath "$INSTDIR\share\locale\vi\LC_MESSAGES"
			File "C:\GNUnet\share\locale\vi\LC_MESSAGES\GNUnet.mo" 
			File "C:\GNUnet\share\locale\vi\LC_MESSAGES\libextractor.mo" 
		SectionEnd
	SectionGroupEnd
	
	Section "Setup" SEC_SETUP
		SectionIn 1 2 3 4
	  SetOutPath "$INSTDIR\bin"
		File "C:\GNUnet\bin\gnunet-setup.exe" 		
		File "C:\GNUnet\bin\libgnunetsetup-0.dll"
    File "C:\GNUnet\bin\libgnunetsetup_qt.dll"

	  SetOutPath "$INSTDIR\share\GNUnet"
		File "C:\GNUnet\share\GNUnet\config-client.scm" 
		File "C:\GNUnet\share\GNUnet\config-daemon.scm"
		File "C:\GNUnet\share\GNUnet\gnunet-logo-color.png"
		File "C:\GNUnet\share\GNUnet\wizard.glade"
    File "C:\GNUnet\share\GNUnet\gnunet-setup.glade"
	SectionEnd
	
	SectionGroup "Server"
		Section "!Base" SEC_SERVER_BASE
			SectionIn 1 2 4
		  SetOutPath "$INSTDIR\bin"

			File "C:\GNUnet\bin\libgnunetcore-0.dll"
			File "C:\GNUnet\bin\gnunetd.exe"
      File "C:\GNUnet\bin\libgnunetip-0.dll" 
			File "C:\GNUnet\bin\libgnunetstats_api-0.dll"
      File "C:\GNUnet\bin\libgnunetmodule_upnp.dll"
      File "C:\GNUnet\bin\libgnunettransport_http.dll"
			File "C:\GNUnet\bin\libgnunettransport_tcp.dll"
			File "C:\GNUnet\bin\libgnunettransport_udp.dll"
			File "C:\GNUnet\bin\libgnunettransport_nat.dll"
      File "C:\GNUnet\bin\libgnunetmodule_advertising.dll"
			File "C:\GNUnet\bin\libgnunetmodule_bootstrap.dll"
			File "C:\GNUnet\bin\libgnunetmodule_fragmentation.dll"
      File "C:\GNUnet\bin\libgnunetmodule_getoption.dll"
      File "C:\GNUnet\bin\libgnunetmodule_hostlist.dll"
			File "C:\GNUnet\bin\libgnunetmodule_identity.dll"
			File "C:\GNUnet\bin\libgnunetmodule_pingpong.dll"
			File "C:\GNUnet\bin\libgnunetmodule_session.dll"
			File "C:\GNUnet\bin\libgnunetmodule_stats.dll"
			File "C:\GNUnet\bin\libgnunetmodule_topology_default.dll"
			File "C:\GNUnet\bin\libgnunetmodule_traffic.dll"
			File "C:\GNUnet\bin\libgnunetmodule_transport.dll"

      ReadRegStr $DATADIR "HKLM" "Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" "Common AppData"
      FindFirst $0 $1 "$DATADIR\GNU\GNUnet\etc\gnunetd.conf"
      StrCmp $1 "" inst_conf
      goto noinst_conf
      inst_conf:
        SetOutPath "$DATADIR\GNU\GNUnet\etc"
        File "C:\GNUnet\etc\gnunetd.conf"
        ; site wide user config (gnunet-auto-share)
        File "C:\GNUnet\etc\gnunet.conf"
      noinst_conf:
        FileClose $0
		SectionEnd

		Section "Filesharing" SEC_SERVER_FS
			SectionIn 1 2 4
		  SetOutPath "$INSTDIR\bin"

			File "C:\GNUnet\bin\libgnunetmodule_fs.dll"
			File "C:\GNUnet\bin\libgnunetmodule_datastore.dll"
			File "C:\GNUnet\bin\libgnunetmodule_sqstore_sqlite.dll"
			File "C:\GNUnet\bin\libgnunetmodule_sqstore_mysql.dll"
			File "C:\GNUnet\bin\libgnunetmodule_kvstore_sqlite.dll"
		SectionEnd

    Section "Chat" SEC_SERVER_CHAT
      SectionIn 1 2 4
      SetOutPath "$INSTDIR\bin"

      File "C:\GNUnet\bin\libgnunetmodule_chat.dll"
    SectionEnd
	SectionGroupEnd
	
	SectionGroup "Client"
		Section "!Configuration files" SEC_CLIENT_CONFIG
			SectionIn 1 3 4
		  ReadEnvStr $USR_PROF "USERPROFILE"
		  StrLen $DIRLEN $USR_PROF
		  IntCmp $DIRLEN 0 no_profile
		  goto cp_conf
		 no_profile:
		  ReadRegStr $USR_PROF "HKCU" "Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" "Personal"
		  StrLen $DIRLEN $USR_PROF
		  IntCmp $DIRLEN 0 gn_dir
		  goto cp_conf
		 gn_dir:
		  StrCpy $USR_PROF "$INSTDIR\home"
		 cp_conf:
		  StrCpy $USR_PROF "$USR_PROF\.gnunet\"
		  SetOutPath $USR_PROF
		  File "C:\GNUnet\etc\gnunet.conf"
		SectionEnd
	
		SectionGroup "Filesharing" SEC_CLIENT_FS
			Section "Base"
			SectionIn 1 3 4
		  SetOutPath "$INSTDIR\bin"

			File "C:\GNUnet\bin\libgnunetcollection-0.dll"
			File "C:\GNUnet\bin\libgnunetecrs-0.dll"
			File "C:\GNUnet\bin\libgnunetfs-0.dll"
			File "C:\GNUnet\bin\libgnunetfsui-0.dll"
      File "C:\GNUnet\bin\libgnunetidentity_api-0.dll"
			File "C:\GNUnet\bin\libgnunetnamespace-0.dll"
			File "C:\GNUnet\bin\libgnuneturitrack-0.dll"			
			SectionEnd
			
			Section "!Keyword extractor" SEC_CLIENT_LE
				SectionIn 1 3 4
			  SetOutPath "$INSTDIR\bin"

				File "C:\GNUnet\bin\libextractor-1.dll"
				File "C:\GNUnet\bin\libextractor_filename.dll"
				File "C:\GNUnet\bin\libextractor_split.dll"
				File "C:\GNUnet\bin\libextractor_lower.dll"
				File "C:\GNUnet\bin\libextractor_thumbnail.dll"
				File "C:\GNUnet\bin\libextractor_translit.dll"
			SectionEnd			

			Section "Text Interface" SEC_CLIENT_TUI
				SectionIn 1 3 4
			  SetOutPath "$INSTDIR\bin"

				File "C:\GNUnet\bin\gnunet-insert.exe"
				File "C:\GNUnet\bin\gnunet-download.exe"
				File "C:\GNUnet\bin\gnunet-search.exe"
				File "C:\GNUnet\bin\gnunet-directory.exe"
				File "C:\GNUnet\bin\gnunet-pseudonym.exe"
				File "C:\GNUnet\bin\gnunet-unindex.exe"
			SectionEnd			

      Section "Graphical Interface" SEC_CLIENT_GUI
        SectionIn 1 3 4
        SetOutPath "$INSTDIR\bin"
        
        File "C:\GNUnet\bin\gnunet-qt.exe"
        File "C:\GNUnet\bin\libgnunetqt_common-0.dll"
        File "C:\GNUnet\bin\libgnunetqtmodule_about.dll"
        File "C:\GNUnet\bin\libgnunetqtmodule_fs.dll"
        File "C:\GNUnet\bin\libgnunetqtmodule_general.dll"
        File "C:\GNUnet\bin\libgnunetqtmodule_stats.dll"
        
        SetOutPath "$INSTDIR\share\gnunet-qt\locale"
        File "C:\GNUnet\share\gnunet-qt\locale\gnunet-qt_de.qm"
      SectionEnd
      
      Section "Automatic sharing"
        SectionIn 1 3 4
        SetOutPath "$INSTDIR\bin"
        
        File "C:\GNUnet\bin\gnunet-auto-share.exe"
;        CreateShortCut "$SMSTARTUP\GNUnet Auto-Share.lnk" "$INSTDIR\bin\gnunet-auto-share.exe"
      SectionEnd
		SectionGroupEnd
    
    SectionGroup "Chat" SEC_CLIENT_CHAT
      Section "Base"
        SectionIn 1 3 4
        SetOutPath "$INSTDIR\bin"
        
        File "C:\GNUnet\bin\libgnunetchat_api-0.dll"
      SectionEnd      

      Section "Text Interface" SEC_CLIENT_CHAT_TUI
        SectionIn 1 3 4
        SetOutPath "$INSTDIR\bin"

        File "C:\GNUnet\bin\gnunet-chat.exe"
      SectionEnd
    SectionGroupEnd    
    

		Section "Statistics" SEC_STATS
			SectionIn 1 2 3 4
		  SetOutPath "$INSTDIR\bin"

			File "C:\GNUnet\bin\gnunet-stats.exe"
		SectionEnd		
	SectionGroupEnd

	SectionGroup "Advanced"
		Section "Diagnostics" SEC_DIAG
			SectionIn 4
		  SetOutPath "$INSTDIR\bin"

			File "C:\GNUnet\bin\gnunet-peer-info.exe"			
			File "C:\GNUnet\bin\gnunet-transport-check.exe"			
		SectionEnd

		Section "Tracekit" SEC_TRACE
			SectionIn 4
		  SetOutPath "$INSTDIR\bin"

			File "C:\GNUnet\bin\gnunet-tracekit.exe"			
      		File "C:\GNUnet\bin\libgnunetmodule_tracekit.dll"  
      		File "C:\GNUnet\bin\libgnunettracekit_api-0.dll"     
		SectionEnd

		Section "TBench" SEC_TBENCH
			SectionIn 4
		  SetOutPath "$INSTDIR\bin"

			File "C:\GNUnet\bin\gnunet-tbench.exe"			
			File "C:\GNUnet\bin\libgnunetmodule_tbench.dll"			
		SectionEnd

		Section "DHT" SEC_DHT
			SectionIn 1 2 4
		  SetOutPath "$INSTDIR\bin"

     	File "C:\GNUnet\bin\libgnunetmodule_dstore_sqlite.dll"
			File "C:\GNUnet\bin\libgnunetmodule_dht.dll"
			File "C:\GNUnet\bin\libgnunetdht_api-0.dll"
		SectionEnd
    
    Section "RPC" SEC_RPC
      SectionIn 1 2 4
      SetOutPath "$INSTDIR\bin"

      File "C:\GNUnet\bin\libgnunetrpc_util-0.dll"
      File "C:\GNUnet\bin\libgnunetmodule_rpc.dll"
    SectionEnd
	SectionGroupEnd
SectionGroupEnd

SectionGroup "GNU libextractor"
	Section "All keyword extractors" SEC_LE_ALL
		SectionIn 1 3 4
	  SetOutPath "$INSTDIR\bin"

    File "C:\GNUnet\bin\libgdk_pixbuf-2.0-0.dll"
    File "C:\GNUnet\bin\libglib-2.0-0.dll"
    File "C:\GNUnet\bin\libgmodule-2.0-0.dll"
    File "C:\GNUnet\bin\libgobject-2.0-0.dll"
    File "C:\GNUnet\bin\libgthread-2.0-0.dll"

		File "C:\GNUnet\bin\jpeg62.dll"
		File "C:\GNUnet\bin\bzip2.dll"
		File "C:\GNUnet\bin\libextractor-1.dll"
		File "C:\GNUnet\bin\libmpeg2.dll"
		File "C:\GNUnet\bin\libgsf-1-114.dll"
		File "C:\GNUnet\bin\libgsf-win32-1-114.dll"
		File "C:\GNUnet\bin\libogg-0.dll"
		File "C:\GNUnet\bin\libvorbis-0.dll"
		File "C:\GNUnet\bin\libvorbisfile-3.dll"
		File "C:\GNUnet\bin\libextractor_asf.dll"
		File "C:\GNUnet\bin\libextractor_deb.dll"
		File "C:\GNUnet\bin\libextractor_dvi.dll"
		File "C:\GNUnet\bin\libextractor_elf.dll"
		File "C:\GNUnet\bin\libextractor_exiv2.dll"
		File "C:\GNUnet\bin\libextractor_gif.dll"
		File "C:\GNUnet\bin\libextractor_hash_md5.dll"
		File "C:\GNUnet\bin\libextractor_hash_rmd160.dll"
		File "C:\GNUnet\bin\libextractor_hash_sha1.dll"
		File "C:\GNUnet\bin\libextractor_html.dll"
		File "C:\GNUnet\bin\libextractor_id3v2.dll"
		File "C:\GNUnet\bin\libextractor_id3v23.dll"
		File "C:\GNUnet\bin\libextractor_id3v24.dll"
		File "C:\GNUnet\bin\libextractor_jpeg.dll"
		File "C:\GNUnet\bin\libextractor_man.dll"
		File "C:\GNUnet\bin\libextractor_mime.dll"
		File "C:\GNUnet\bin\libextractor_mp3.dll"
		File "C:\GNUnet\bin\libextractor_mpeg.dll"
		File "C:\GNUnet\bin\libextractor_ogg.dll"
		File "C:\GNUnet\bin\libextractor_ole2.dll"
		File "C:\GNUnet\bin\libextractor_oo.dll"
		File "C:\GNUnet\bin\libextractor_pdf.dll"
		File "C:\GNUnet\bin\libextractor_png.dll"
		File "C:\GNUnet\bin\libextractor_ps.dll"
		File "C:\GNUnet\bin\libextractor_qt.dll"
		File "C:\GNUnet\bin\libextractor_real.dll"
		File "C:\GNUnet\bin\libextractor_riff.dll"
		File "C:\GNUnet\bin\libextractor_rpm.dll"
		File "C:\GNUnet\bin\libextractor_tar.dll"
		File "C:\GNUnet\bin\libextractor_tiff.dll"
		File "C:\GNUnet\bin\libextractor_wav.dll"
		File "C:\GNUnet\bin\libextractor_zip.dll"
	SectionEnd
SectionGroupEnd

SectionGroup "Dependencies"
	Section "Base" SEC_DEPS_BASE
		SectionIn RO

		SetOutPath "$INSTDIR\bin"
    
    File "C:\GNUnet\bin\libxml2.dll"
		File "C:\GNUnet\bin\iconv.dll"
		File "C:\GNUnet\bin\intl.dll"
		File "C:\GNUnet\bin\libcurl-3.dll"		
		File "C:\GNUnet\bin\libgcrypt-11.dll"
		File "C:\GNUnet\bin\libgpg-error-0.dll"
		File "C:\GNUnet\bin\libgmp.dll"
		File "C:\GNUnet\bin\libguile-17.dll"		
		File "C:\GNUnet\bin\libiconv-2.dll"
		File "C:\GNUnet\bin\libintl-2.dll"
		File "C:\GNUnet\bin\libintl-3.dll"
		File "C:\GNUnet\bin\libltdl-3.dll"
    File "C:\GNUnet\bin\libmicrohttpd-3.dll"
		File "C:\GNUnet\bin\libmysql.dll"
		File "C:\GNUnet\bin\libplibc-1.dll"
		File "C:\GNUnet\bin\libsqlite3-0.dll"
		File "C:\GNUnet\bin\pthreadGC2.dll"
		File "C:\GNUnet\bin\zlib1.dll"

    SetOutPath "$INSTDIR\share"
    File /r "C:\GNUnet\share\guile"
	SectionEnd
	
	Section "!GUI libs (Qt)" SEC_DEPS_GTK
		SectionIn 1 3 4

		SetOutPath "$INSTDIR\bin"
    File "C:\GNUnet\bin\mingwm10.dll"
    File "C:\GNUnet\bin\QtCore4.dll"
    File "C:\GNUnet\bin\QtGui4.dll"
    File "C:\GNUnet\bin\QtSvg4.dll"
    File "C:\GNUnet\bin\QtXml4.dll"
    
    SetOutPath "$INSTDIR\bin\imageformats"
    File "C:\GNUnet\bin\imageformats\qgif1.dll"
    File "C:\GNUnet\bin\imageformats\qjpeg1.dll"
    File "C:\GNUnet\bin\imageformats\qmng1.dll"
    File "C:\GNUnet\bin\imageformats\qsvg1.dll"

	SectionEnd
SectionGroupEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\bin\gnu.ico"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "${PRODUCT_STARTMENU_REGVAL}" "$ICONS_GROUP"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegStr HKLM "Software\GNU\GNUnet" "InstallDir" "$INSTDIR"
  SetOutPath "$INSTDIR\bin"
SectionEnd

; Section descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_GNUNET} "GNUnet"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_GNUNET_BASE} "GNUnet core"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_LANG} "Translated messages"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_LANG_DE} "German messages"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_LANG_RW} "Kinyarwanda messages"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_LANG_SV} "Swedish messages"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_LANG_VI} "Vietnamese messages"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_SETUP} "GNUnet configuration application"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_SERVER_BASE} "GNUnet server core"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_SERVER_FS} "Support for filesharing"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_CLIENT_FS} "Client tools for filesharing"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_CLIENT_LE} "Basic keyword extractors"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_CLIENT_TUI} "Textbased user interfaces"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_CLIENT_GUI} "Graphical user interface (gnunet-qt)"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_STATS} "Tool to display server statistics"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_DIAG} "Advanced diagnostic tools"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_TRACE} "Tracekit"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_TBENCH} "TBench"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_DHT} "Distributed Hash Tables"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_RPC} "Remote Procedure Calls"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_LE_ALL} "Sophisticated keyword extractors (mp3, pdf, zip...)"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_DEPS_BASE} "3rd party software required by GNUnet"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_DEPS_GTK} "3rd party software required by GNUnet Setup and the GUI"
!insertmacro MUI_FUNCTION_DESCRIPTION_END


Function .onInit
  InitPluginsDir

  
  StrCmp $LANGUAGE "1031" 0 english
  StrCpy $LANGCODE "de"
  goto end
 english:
  StrCpy $LANGCODE "en"

end:
FunctionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully deinstalled."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Do you want to deinstall $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Function ShowReadme
  Exec "notepad $INSTDIR\README"
FunctionEnd

Section Uninstall
	; Uninstall service
	SetOutPath "$INSTDIR\bin\"
	ExecWait '"$INSTDIR\bin\gnunet-win-tool.exe" -u'
	SetOutPath "$INSTDIR\..\"

  ReadRegStr $ICONS_GROUP ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "${PRODUCT_STARTMENU_REGVAL}"
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  
	Delete "$INSTDIR\AUTHORS"
	Delete "$INSTDIR\COPYING"
	Delete "$INSTDIR\ChangeLog"
	Delete "$INSTDIR\PLATFORMS"
	Delete "$INSTDIR\README"
	Delete "$INSTDIR\UPDATING"
	Delete "$INSTDIR\bin\gnu.ico"	
	Delete "$INSTDIR\bin\config.ico"	
	Delete "$INSTDIR\bin\bzip2.dll"
	Delete "$INSTDIR\bin\gnunet-dht-join.exe"
	Delete "$INSTDIR\bin\gnunet-dht-query.exe"
	Delete "$INSTDIR\bin\gnunet-directory.exe"
	Delete "$INSTDIR\bin\gnunet-download.exe"
	Delete "$INSTDIR\bin\gnunet-insert.exe"
	Delete "$INSTDIR\bin\gnunet-peer-info.exe"			
	Delete "$INSTDIR\bin\gnunet-pseudonym.exe"
	Delete "$INSTDIR\bin\gnunet-search.exe"
	Delete "$INSTDIR\bin\gnunet-setup.exe" 		
	Delete "$INSTDIR\bin\libgnunetsetup.dll" 
	Delete "$INSTDIR\bin\libgnunetsetup-0.dll" 
	Delete "$INSTDIR\bin\libgnunetsetup_curses.dll"
  Delete "$INSTDIR\bin\libgnunetsetup_qt.dll"
		
	Delete "$INSTDIR\bin\gnunet-stats.exe"
	Delete "$INSTDIR\bin\gnunet-tbench.exe"			
	Delete "$INSTDIR\bin\gnunet-tbench.exe"			
	Delete "$INSTDIR\bin\gnunet-tracekit.exe"			
	Delete "$INSTDIR\bin\gnunet-transport-check.exe"			
	Delete "$INSTDIR\bin\gnunet-unindex.exe"
	Delete "$INSTDIR\bin\gnunet-update.exe" 
	Delete "$INSTDIR\bin\gnunet-win-tool.exe"
	Delete "$INSTDIR\bin\gnunetd.exe"
	Delete "$INSTDIR\bin\iconv.dll"
	Delete "$INSTDIR\bin\intl.dll"
	Delete "$INSTDIR\bin\jpeg62.dll"
	Delete "$INSTDIR\bin\libpng13.dll"
	Delete "$INSTDIR\bin\libatk-1.0-0.dll"
	Delete "$INSTDIR\bin\libextractor-1.dll"
	Delete "$INSTDIR\bin\libextractor_asf.dll"
	Delete "$INSTDIR\bin\libextractor_deb.dll"
	Delete "$INSTDIR\bin\libextractor_dvi.dll"
	Delete "$INSTDIR\bin\libextractor_elf.dll"
	Delete "$INSTDIR\bin\libextractor_exiv2.dll"
	Delete "$INSTDIR\bin\libextractor_filename.dll"
	Delete "$INSTDIR\bin\libextractor_gif.dll"
	Delete "$INSTDIR\bin\libextractor_hash_md5.dll"
	Delete "$INSTDIR\bin\libextractor_hash_rmd160.dll"
	Delete "$INSTDIR\bin\libextractor_hash_sha1.dll"
	Delete "$INSTDIR\bin\libextractor_html.dll"
	Delete "$INSTDIR\bin\libextractor_id3v2.dll"
	Delete "$INSTDIR\bin\libextractor_id3v23.dll"
	Delete "$INSTDIR\bin\libextractor_id3v24.dll"
	Delete "$INSTDIR\bin\libextractor_jpeg.dll"
	Delete "$INSTDIR\bin\libextractor_lower.dll"
	Delete "$INSTDIR\bin\libextractor_man.dll"
	Delete "$INSTDIR\bin\libextractor_mime.dll"
	Delete "$INSTDIR\bin\libextractor_mp3.dll"
	Delete "$INSTDIR\bin\libextractor_mpeg.dll"
	Delete "$INSTDIR\bin\libextractor_ogg.dll"
	Delete "$INSTDIR\bin\libextractor_ole2.dll"
	Delete "$INSTDIR\bin\libextractor_oo.dll"
	Delete "$INSTDIR\bin\libextractor_pdf.dll"
	Delete "$INSTDIR\bin\libextractor_png.dll"
	Delete "$INSTDIR\bin\libextractor_ps.dll"
	Delete "$INSTDIR\bin\libextractor_qt.dll"
	Delete "$INSTDIR\bin\libextractor_real.dll"
	Delete "$INSTDIR\bin\libextractor_riff.dll"
	Delete "$INSTDIR\bin\libextractor_rpm.dll"
	Delete "$INSTDIR\bin\libextractor_split.dll"
	Delete "$INSTDIR\bin\libextractor_tar.dll"
	Delete "$INSTDIR\bin\libextractor_thumbnail.dll"
	Delete "$INSTDIR\bin\libextractor_tiff.dll"
	Delete "$INSTDIR\bin\libextractor_translit.dll"
	Delete "$INSTDIR\bin\libextractor_wav.dll"
	Delete "$INSTDIR\bin\libextractor_zip.dll"
	Delete "$INSTDIR\bin\libcurl-3.dll"	
	Delete "$INSTDIR\bin\libgcrypt.dll"
	Delete "$INSTDIR\bin\libgcrypt-11.dll"
	Delete "$INSTDIR\bin\libgpg-error-0.dll"
	Delete "$INSTDIR\bin\libguile-17.dll"
  RMDir /r /REBOOTOK "$INSTDIR\share\guile"
	Delete "$INSTDIR\bin\libgdk-0.dll"
	Delete "$INSTDIR\bin\libgdk-win32-2.0-0.dll"
	Delete "$INSTDIR\bin\libgdk_pixbuf-2.0-0.dll"
	Delete "$INSTDIR\bin\libglade-2.0-0.dll"
	Delete "$INSTDIR\bin\libglib-2.0-0.dll"
	Delete "$INSTDIR\bin\libgmodule-2.0-0.dll"
	Delete "$INSTDIR\bin\libgmp.dll"
	Delete "$INSTDIR\bin\libgnunetcore-0.dll"
	Delete "$INSTDIR\bin\libgnunetdht_api-0.dll"
	Delete "$INSTDIR\bin\libgnunetdht_datastore_memory-0.dll"
  Delete "$INSTDIR\bin\ibgnunetmodule_dstore.dll"
  Delete "$INSTDIR\bin\libgnunetmodule_dstore_sqlite.dll"
	Delete "$INSTDIR\bin\libgnunetecrs-0.dll"
  Delete "$INSTDIR\bin\libgnunetecrs_core-0.dll"
	Delete "$INSTDIR\bin\libgnunetfs-0.dll"
  Delete "$INSTDIR\bin\libgnunetfsui-0.dll"
  Delete "$INSTDIR\bin\libgnunetidentity_api-0.dll"
	Delete "$INSTDIR\bin\libgnuneturitrack-0.dll"
	Delete "$INSTDIR\bin\libgnunetnamespace-0.dll"
	Delete "$INSTDIR\bin\libgnunetcollection-0.dll"
	Delete "$INSTDIR\bin\libgnunetgetoption_api-0.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_advertising.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_bootstrap.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_chat.dll"			
	Delete "$INSTDIR\bin\libgnunetmodule_datastore.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_dht.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_fragmentation.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_fs.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_gap.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_getoption.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_identity.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_pingpong.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_rpc.dll"
  Delete "$INSTDIR\bin\libgnunetmodule_rpc_util-0.dll"
  Delete "$INSTDIR\bin\libgnunetrpc_util-0.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_session.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_sqstore_mysql.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_sqstore_sqlite.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_kvstore_sqlite.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_stats.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_tbench.dll"			
	Delete "$INSTDIR\bin\libgnunetmodule_topology_default.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_topology_f2f.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_tracekit.dll"			
	Delete "$INSTDIR\bin\libgnunetmodule_traffic.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_traffic_api-0.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_transport.dll"
	Delete "$INSTDIR\bin\libgnunetstats_api-0.dll"
	Delete "$INSTDIR\bin\libgnunettransport_http.dll"
	Delete "$INSTDIR\bin\libgnunettransport_nat.dll"
	Delete "$INSTDIR\bin\libgnunettransport_tcp.dll"
  Delete "$INSTDIR\bin\libgnunettransport_tcp_old.dll"
	Delete "$INSTDIR\bin\libgnunettransport_udp.dll"
  Delete "$INSTDIR\bin\libgnunetmodule_upnp.dll"
  Delete "$INSTDIR\bin\libgnunetutil-1.dll"
  Delete "$INSTDIR\bin\libgnunetutil-2.dll"
  Delete "$INSTDIR\bin\libgnunetutil-3.dll"
	Delete "$INSTDIR\bin\libgnunetmodule_state.dll"
  Delete "$INSTDIR\bin\libgnunetip-0.dll"
  Delete "$INSTDIR\bin\libgnunettraffic_api-0.dll"
	Delete "$INSTDIR\bin\libgnunetutil_config-0.dll"
	Delete "$INSTDIR\bin\libgnunetutil_cron-0.dll"
	Delete "$INSTDIR\bin\libgnunetutil_crypto-0.dll"
	Delete "$INSTDIR\bin\libgnunetutil_containers-0.dll"
	Delete "$INSTDIR\bin\libgnunetutil_logging-0.dll"
	Delete "$INSTDIR\bin\libgnunetutil_network_client-0.dll"
	Delete "$INSTDIR\bin\libgnunetutil_boot-0.dll"
	Delete "$INSTDIR\bin\libgobject-2.0-0.dll"
	Delete "$INSTDIR\bin\libgthread-2.0-0.dll"
	Delete "$INSTDIR\bin\libiconv-2.dll"
	Delete "$INSTDIR\bin\libintl-2.dll"
	Delete "$INSTDIR\bin\libintl-3.dll"
	Delete "$INSTDIR\bin\libltdl-3.dll"
  Delete "$INSTDIR\bin\libmicrohttpd-3.dll"
  Delete "$INSTDIR\bin\libmysql.dll"
	Delete "$INSTDIR\bin\libogg-0.dll"
	Delete "$INSTDIR\bin\libpango-1.0-0.dll"
	Delete "$INSTDIR\bin\libpangowin32-1.0-0.dll"
	Delete "$INSTDIR\bin\libplibc-1.dll"
	Delete "$INSTDIR\bin\libmpeg2.dll"
	Delete "$INSTDIR\bin\libgsf-1-114.dll"
	Delete "$INSTDIR\bin\libgsf-win32-1-114.dll"
	Delete "$INSTDIR\bin\libpng12.dll"
	Delete "$INSTDIR\bin\libsqlite3-0.dll"
	Delete "$INSTDIR\bin\libvorbis-0.dll"
	Delete "$INSTDIR\bin\libvorbisfile-3.dll"
	Delete "$INSTDIR\bin\libxml2.dll"
	Delete "$INSTDIR\bin\pthreadGC1.dll"
	Delete "$INSTDIR\bin\pthreadGC2.dll"
	Delete "$INSTDIR\bin\zlib1.dll"
  
  Delete "$INSTDIR\bin\gnunet-qt.exe"
  Delete "$INSTDIR\bin\libgnunetqt_common-0.dll"
  Delete "$INSTDIR\bin\libgnunetqtmodule_about.dll"
  Delete "$INSTDIR\bin\libgnunetqtmodule_fs.dll"
  Delete "$INSTDIR\bin\libgnunetqtmodule_general.dll"
  Delete "$INSTDIR\bin\libgnunetqtmodule_stats.dll"
  Delete "$INSTDIR\bin\QtCore4.dll"
  Delete "$INSTDIR\bin\QtGui4.dll"
  Delete "$INSTDIR\bin\QtSvg4.dll"
  Delete "$INSTDIR\bin\QtXml4.dll"
  
	RmDir /REBOOTOK "$INSTDIR\bin"
	
	RmDir /REBOOTOK "$INSTDIR\etc"

  RmDir /REBOOTOK "$INSTDIR\lib"
  
	Delete "$INSTDIR\share\GNUnet\config-client.in" 
	Delete "$INSTDIR\share\GNUnet\config-daemon.in"
	Delete "$INSTDIR\share\GNUnet\config-client.scm" 
	Delete "$INSTDIR\share\GNUnet\config-daemon.scm"
	Delete "$INSTDIR\share\GNUnet\wizard.glade"
  Delete "$INSTDIR\share\GNUnet\gnunet-setup.glade"
	Delete "$INSTDIR\share\GNUnet\gnunet-logo-color.png"
  RmDir /REBOOTOK "$INSTDIR\share\GNUnet"
	Delete "$INSTDIR\share\locale\de\LC_MESSAGES\GNUnet.mo" 
	Delete "$INSTDIR\share\locale\de\LC_MESSAGES\libextractor.mo" 
  RmDir /REBOOTOK "$INSTDIR\share\locale\de\LC_MESSAGES"
  RmDir /REBOOTOK "$INSTDIR\share\locale\de"
	Delete "$INSTDIR\share\locale\rw\LC_MESSAGES\GNUnet.mo" 
	Delete "$INSTDIR\share\locale\rw\LC_MESSAGES\libextractor.mo" 
  RmDir /REBOOTOK "$INSTDIR\share\locale\rw\LC_MESSAGES"
  RmDir /REBOOTOK "$INSTDIR\share\locale\rw"
	Delete "$INSTDIR\share\locale\vi\LC_MESSAGES\GNUnet.mo" 
	Delete "$INSTDIR\share\locale\vi\LC_MESSAGES\libextractor.mo" 
  RmDir /REBOOTOK "$INSTDIR\share\locale\vi\LC_MESSAGES"
  RmDir /REBOOTOK "$INSTDIR\share\locale\vi"
	Delete "$INSTDIR\share\locale\sv\LC_MESSAGES\GNUnet.mo" 
	Delete "$INSTDIR\share\locale\sv\LC_MESSAGES\libextractor.mo" 
  RmDir /REBOOTOK "$INSTDIR\share\locale\sv\LC_MESSAGES"
  RmDir /REBOOTOK "$INSTDIR\share\locale\sv"
  RmDir /REBOOTOK "$INSTDIR\share\locale\fr\LC_MESSAGES"
  RmDir /REBOOTOK "$INSTDIR\share\locale\fr"
  RmDir /REBOOTOK "$INSTDIR\share\locale\tr\LC_MESSAGES"
  RmDir /REBOOTOK "$INSTDIR\share\locale\tr"
  Delete "$INSTDIR\share\locale\es\LC_MESSAGES\GNUnet.mo" 
  RmDir /REBOOTOK "$INSTDIR\share\locale\es\LC_MESSAGES"
  RmDir /REBOOTOK "$INSTDIR\share\locale\es"
  RmDir /REBOOTOK "$INSTDIR\share\locale"
  RmDir /REBOOTOK "$INSTDIR\share"

	RmDir /r /REBOOTOK $INSTDIR\share\icons
	RmDir /REBOOTOK $INSTDIR\share

  Delete "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Website.lnk"
  Delete "$DESKTOP\GNUnet.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\GNUnet.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\$(confwizard).lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\$(gnunetdconfig).lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\$(gnunetclientconfig).lnk"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
;  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  DeleteRegKey HKLM "Software\GNU\GNUnet"
  
  MessageBox MB_YESNO "$(deleteall)" IDNO end
  ReadEnvStr $USR_PROF "USERPROFILE"
  StrLen $DIRLEN $USR_PROF
  IntCmp $DIRLEN 0 no_profile
  goto rm_conf
 no_profile:
  ReadRegStr $USR_PROF "HKCU" "Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" "Personal"
  StrLen $DIRLEN $USR_PROF
  IntCmp $DIRLEN 0 gn_dir
  goto rm_conf
 gn_dir:
  StrCpy $USR_PROF "$INSTDIR\home"
 rm_conf:
  StrCpy $USR_PROF "$USR_PROF\.gnunet"

  RMDir /REBOOTOK $USR_PROF
  RMDir /REBOOTOK "$SMPROGRAMS\$ICONS_GROUP"
  RmDir /r /REBOOTOK "$INSTDIR"
  ReadRegStr $DATADIR "HKLM" "Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" "Common AppData"
  RmDir /r /REBOOTOK "$DATADIR\GNU\GNUnet"
 end:
  SetAutoClose true
SectionEnd
