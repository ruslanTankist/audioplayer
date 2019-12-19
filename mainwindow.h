#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "playlist.h"
#include "notelist.h"
#include <QtMultimedia/QMediaPlayer>
#include "QTimer"
#include "QPalette"
#include "vector"
#include "QKeyEvent"
#include "QLineEdit"
#include "utils.h"

using namespace std;

string timetostr(int inttime);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_add_clicked();

    void on_remove_clicked();

    void on_save_clicked();

    void on_play_clicked();

    void on_volumeBar_valueChanged(int value);

    void on_seekBar_sliderMoved(int position);

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_forward_clicked();

    void on_back_clicked();

    void on_mute_clicked();

    void on_repeat_clicked();

    void on_shuffle_clicked();

    void update();

    void on_searchBar_textChanged(const QString &arg1);

    void on_add_note_clicked();

    void on_remove_note_clicked();

    void on_save_note_clicked();

private:
    void updateList();

    void loadTrack();

    void next();

    void back();

    void shufflePlaylist();

    int getIndex();

    int getIndexNote();

    void updateNoteList();

    bool repeat = false;

    bool muted = false;

    bool shuffle = false;

    int lCounter = 0;

    Playlist playlist;

    NoteList notelist;

    Ui::MainWindow *ui;

    QTimer *updater = new QTimer(this);

    QMediaPlayer *player = new QMediaPlayer();

    vector<unsigned short int> shuffledPlaylist;

protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
