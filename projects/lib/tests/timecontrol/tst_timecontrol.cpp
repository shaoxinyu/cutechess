#include <QtTest/QTest>
#include <timecontrol.h>

class tst_TimeControl: public QObject
{
	Q_OBJECT

	private slots:
		void parseMilliseconds();
		void serializeMilliseconds();
};

void tst_TimeControl::parseMilliseconds()
{
	TimeControl tc("40/1.001+0.002");
	QCOMPARE(tc.movesPerTc(), 40);
	QCOMPARE(tc.timePerTc(), 1001);
	QCOMPARE(tc.timeIncrement(), 2);

	TimeControl minutes("2:00.001");
	QCOMPARE(minutes.timePerTc(), 120001);

	TimeControl minimum("0.001");
	QCOMPARE(minimum.timePerTc(), 1);
}

void tst_TimeControl::serializeMilliseconds()
{
	TimeControl tc;
	tc.setMovesPerTc(40);
	tc.setTimePerTc(1234567);
	tc.setTimeIncrement(1);

	QCOMPARE(tc.toString(), QString("40/1234.567+0.001"));
	QCOMPARE(tc.toVerboseString(),
		 QString("40 moves in 1234.567 sec, 0.001 sec increment"));

	TimeControl roundTrip(tc.toString());
	QCOMPARE(roundTrip.movesPerTc(), tc.movesPerTc());
	QCOMPARE(roundTrip.timePerTc(), tc.timePerTc());
	QCOMPARE(roundTrip.timeIncrement(), tc.timeIncrement());
}

QTEST_MAIN(tst_TimeControl)
#include "tst_timecontrol.moc"
