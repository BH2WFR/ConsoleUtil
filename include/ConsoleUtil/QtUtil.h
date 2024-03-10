/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/ConsoleUtil
  Author:		BH2WFR
*/
#ifndef CONSOLEUTIL_QT_UTIL_H__
#define CONSOLEUTIL_QT_UTIL_H__

#ifdef __cplusplus
#include <ConsoleUtil/CppUtil.h>


//===================== Qt Utils ==========================
#if defined(QT_CORE_LIB) || defined(QT_VERSION)


//* Qt5 high DPI support since Qt5.6, and fractional scaling support since Qt5.14
//  in Qt6, high DPI and fractional scaling support is enabled by default and no need for this macro.
//  pls #include<QApplication> first before #include of this header.
#if ((QT_VERSION >= QT_VERSION_CHECK(5,6,0)) && (QT_VERSION < QT_VERSION_CHECK(5,14,0)))
	#define CUTIL_QT5_HIGH_DPI() \
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); \
		QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
		
#elif ((QT_VERSION >= QT_VERSION_CHECK(5,14,0)) && (QT_VERSION < QT_VERSION_CHECK(6,0,0)))
	#define CUTIL_QT5_HIGH_DPI() \
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); \
		QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); \
		QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
		
#else // QT_VERSION ( >= 6.0.0 || <= 5.5.0 )
	#define CUTIL_QT5_HIGH_DPI()
	
#endif // QT_VERSION

//* Set QTextCodec default encoding to UTF-8,
//  or cannot correctly print chinese characters via qDebug() if code is saved in UTF-8 encoding;
//  pls #include<QTextCodec> first before #include of this header.
//  in MSVC Compiler, compiler argument "/utf-8" is required if code is saved in UTF-8 encoding;
//  	in CMake, you should add "set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")"
//  In Qt6, QTextCodec module is deleted and contained in Qt5 Compatibility Module.
#if defined(QTEXTCODEC_H)
	#define CUTIL_QT5_TEXTCODEC_SET(_STR)	QTextCodec::setCodecForLocale(QTextCodec::codecForName(_STR));
#else //. !QTEXTCODEC_H
	#define CUTIL_QT5_TEXTCODEC_SET(_STR)
#endif // QTEXTCODEC_H

#define CUTIL_QT5_TEXTCODEC_UTF8()		CUTIL_QT5_TEXTCODEC_SET("UTF-8");
#define CUTIL_QT5_TEXTCODEC_GBK()		CUTIL_QT5_TEXTCODEC_SET("GB18030");
#define CUTIL_QT5_TEXTCODEC_BIG5()		CUTIL_QT5_TEXTCODEC_SET("Big5");
#define CUTIL_QT5_TEXTCODEC_EUCKR()		CUTIL_QT5_TEXTCODEC_SET("EUC-KR");
#define CUTIL_QT5_TEXTCODEC_EUCJP()		CUTIL_QT5_TEXTCODEC_SET("EUC-JP");
#define CUTIL_QT5_TEXTCODEC_JIS()		CUTIL_QT5_TEXTCODEC_SET("Shift-JIS");


//* qDebug() without spaces or quotes
//  pls #include<QDebug> first before this header #include
#ifdef QDEBUG_H
	#define CUTIL_QDEBUG_N  qDebug().noquote() 		  	 // qDebug() without quotes
	#define CUTIL_QDEBUG_NN qDebug().nospace().noquote() // qDebug() without spaces and quotes
		// example: CUTIL_QDEBUG_N << "test" << 1;
	
#endif

/*
* example:
	#include <qglobal.h>
	#include <QApplication>
	#include <QDebug>
	#include <QTextCodec> // include Qt headers first
	
	#include <ConsoleUtil/ConsoleUtil.h> // <QtUtil.h> has been wrapped in this header.
	
	int main(int argc, char* argv[])
	{
		CUTIL_QT5_HIGH_DPI(); 	  	//* enable Qt5 high DPI support
		
		CUTIL_CHCP_ENCODING_UTF8();
		CUTIL_QT5_TEXTCODEC_UTF8(); //* set Qt default text encoding to UTF-8
		
		QApplication app(argc, argv); // you must create QCoreApplication after these macros.
		
		return app.exec();
	}
*/





#endif // QT_CORE_LIB || QT_VERSION

#endif // __cplusplus

#endif // CONSOLEUTIL_QT_UTIL_H__
