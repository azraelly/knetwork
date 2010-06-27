/* -*- C++ -*- */
// $Id: QtReactor_Test.h 79346 2007-08-14 23:29:36Z sowayaa $
#ifndef QTREACTOR_TEST_H
#define QTREACTOR_TEST_H

#include <qapplication.h>
#include <qtimer.h>

class QTestApplication: public QApplication
{
  Q_OBJECT
public:
  typedef QApplication inherited;
public:
  QTestApplication( int argc, char *argv[] );
  virtual void exec( int msec = 0 );
public slots:
  virtual void finishTest(); //!< slot to finish the test, connected to finishTimer_
private:
  QTimer finishTimer_; //!< timer to finish the test
};

#endif /*QTREACTOR_TEST_H*/
