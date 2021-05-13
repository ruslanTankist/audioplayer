#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QDesktopServices"
#include "algorithm"
#include "iostream"
#include "string"
#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(this->geometry().width(),this->geometry().height());

    updateList();

    connect(updater, SIGNAL(timeout()), this, SLOT(update()));

    player->setVolume(100);

    ui->listWidget->setCurrentRow(0);

    if(ui->listWidget->count() != 0){
        loadTrack();
        loadNotes();
        player->pause();
        updater->start();
    }

    ui->listWidgetNotes->setCurrentRow(0);
    ui->error_message_label->setStyleSheet( "QLabel { color : red }; " );

    updateNoteList();
}



MainWindow::~MainWindow()
{
    delete ui;
}

//add mp3 location to file "playlist"
void MainWindow::on_add_clicked()
{
    bool startUpdater = false;if(ui->listWidget->count() == 0) startUpdater = true;
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"));
    if(!files.empty())
    {
        playlist.add(files);
        updateList();
        ui->save->setChecked(false);
        if(shuffle) shufflePlaylist();
        if(startUpdater) updater->start();
    }
}

void MainWindow::on_remove_clicked()
{
    int index = getIndex();
    if(index != -1)
    {
       playlist.remove(index);
       updateList();
       ui->listWidget->setCurrentRow(index);
       ui->save->setChecked(false);
       if(shuffle) shufflePlaylist();
    }
}

void MainWindow::on_save_clicked()
{
    playlist.save();
    ui->save->setChecked(true);
}

//load & play track
void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    lCounter = getIndex();

    ui->play->setChecked(false);
    ui->searchBar->clear();

    loadTrack();
    player->play();

    loadNotes();
}


void MainWindow::on_play_clicked()
{
    if(ui->listWidget->count() != 0) {
        if(player->state() == QMediaPlayer::PlayingState)
        {
            player->pause();
        }
       else
       {
            player->play();
            updater->start();
       }
    }
}

void MainWindow::on_forward_clicked()
{   if(ui->listWidget->count() != 0)
    if(repeat)
    {
        repeat = !repeat;next();repeat = !repeat;
    }
    else
    {
        next();
    }
}

void MainWindow::on_back_clicked()
{   if(ui->listWidget->count() != 0)
    if(player->position() > 3000)
    {
       player->setPosition(0);
    }
    else
    {
        back();
    }
}

void MainWindow::on_volumeBar_valueChanged(int value)
{
    player->setVolume(value);
    (value != 0)?ui->mute->setChecked(false):ui->mute->setChecked(true);
}

void MainWindow::on_seekBar_sliderMoved(int position)
{
    player->setPosition(player->duration() / 1000 * position);
}

void MainWindow::on_mute_clicked()
{
    muted = !muted;
    if (muted) {
        player->setVolume(0);
        ui->mute->setText("unmute");
    } else {
        player->setVolume(ui->volumeBar->value());
        ui->mute->setText("mute");
    }
}

void MainWindow::on_repeat_clicked()
{
     repeat = !repeat;
}


void MainWindow::on_shuffle_clicked()
{
    shuffle = !shuffle;
    if(shuffle)
        shufflePlaylist();
}

void MainWindow::update()
{   if(!ui->seekBar->isSliderDown())
        ui->seekBar->setValue((double)player->position()/player->duration() * 1000);

    if(player->state() == QMediaPlayer::StoppedState)
    {
        next();
    }

    ui->labelTime->setText(QString::fromStdString(timetostr(player->position() / 1000)));
}

void MainWindow::updateList()
{
    ui->listWidget->clear();
    ui->listWidget->addItems(playlist.getTracksNameList());
}

int MainWindow::getIndex()
{
    return ui->listWidget->currentIndex().row();
}

int MainWindow::getIndexNote()
{
    return ui->listWidgetNotes->currentIndex().row();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return :
    {
        lCounter = getIndex();
        if(lCounter != -1)
        {
            ui->play->setChecked(false);
            ui->searchBar->clear();

           loadTrack();
           player->play();
        }
        break;
    }
    case Qt::Key_Up :
    {
        if(!ui->listWidgetNotes->hasFocus())
        {
                int ind = getIndex() - 1;if(ind < 0)ind = ui->listWidget->count() - 1;
                ui->listWidget->setCurrentRow(ind);
        } else {
                int ind = getIndexNote() - 1;if(ind < 0)ind = ui->listWidgetNotes->count() - 1;
                ui->listWidgetNotes->setCurrentRow(ind);
        }
        break;
    }
    case Qt::Key_Down :
    {
        if(!ui->listWidgetNotes->hasFocus())
        {
            int ind = getIndex() + 1;if(ind >= ui->listWidget->count())ind = 0;
            ui->listWidget->setCurrentRow(ind);
        } else {
            int ind = getIndexNote() + 1;if(ind >= ui->listWidgetNotes->count())ind = 0;
            ui->listWidgetNotes->setCurrentRow(ind);
        }
        break;
    }
    }
}

void MainWindow::next()
{
    lCounter++;

    if(repeat)
    {
        lCounter--;
    }

    if(lCounter >= ui->listWidget->count())
        lCounter = 0;

    (!shuffle or repeat) ? ui->listWidget->setCurrentRow(lCounter) : ui->listWidget->setCurrentRow(shuffledPlaylist[lCounter]);

    ui->play->setChecked(false);
    ui->searchBar->clear();

    loadTrack();
    player->play();

}

void MainWindow::back()
{
     lCounter--;

     if(lCounter < 0)
        lCounter = ui->listWidget->count() - 1;


     (!shuffle) ? ui->listWidget->setCurrentRow(lCounter) : ui->listWidget->setCurrentRow(shuffledPlaylist[lCounter]);

     ui->play->setChecked(false);
     ui->searchBar->clear();

     loadTrack();
     player->play();
}

void MainWindow::shufflePlaylist()
{
    shuffledPlaylist.resize(0);

    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        shuffledPlaylist.push_back(i);
    }

    random_shuffle(shuffledPlaylist.begin(), shuffledPlaylist.end());
}

void MainWindow::loadTrack()
{
     QString qstr = QString::fromStdString(playlist.tracks[getIndex()].getLocation());
     player->setMedia(QUrl::fromLocalFile(qstr));
     qstr = QString::fromStdString(playlist.tracks[getIndex()].getName());
     ui->currentSong->setText(qstr);
}

void MainWindow::on_searchBar_textChanged(const QString &arg1)
{
    if(ui->searchBar->text().toStdString() != "")
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(ui->listWidget->item(i)->text().toLower().toStdString().find(arg1.toLower().toStdString()) != string::npos )
        {
            ui->listWidget->setCurrentRow(i);
            break;
        }
    }

}

//реализация заметок

void MainWindow::updateNoteList()
{
    ui->listWidgetNotes->clear();
    ui->listWidgetNotes->addItems(notelist.getNoteList());
}

void MainWindow::on_add_note_clicked()
{
    bool startUpdater = false;if(ui->listWidgetNotes->count() == 0) startUpdater = true;
        QStringList newnote;
        if(!playlist.tracks.empty())
        {
            if(ui->textEditNote->toPlainText() != "")
            {
                ui->error_message_label->setText("");
                QString note_input = ui->textEditNote->toPlainText() + "@" + QString::number(player->position()/1000);
                newnote << note_input;
                if(startUpdater) updater->start();
                notelist.add(newnote);
                updateNoteList();
                ui->save_note->setChecked(false);
                if(startUpdater) updater->start();
            } else {
                ui->error_message_label->setText("Невозможно добавить пустую заметку");
            }
        } else {
            ui->error_message_label->setText("Нет треков, чтобы добавлять к ним записи");
        }
}

void MainWindow::on_remove_note_clicked()
{
    qDebug() << "remove clicked";
    int index = getIndexNote();
    if(index != -1)
    {
       notelist.remove(index);
       updateNoteList();
       ui->listWidgetNotes->setCurrentRow(index);
       ui->save_note->setChecked(false);
    }
}

void MainWindow::on_save_note_clicked()
{
    notelist.save();
    ui->save_note->setChecked(true);
}

void MainWindow::loadNotes()
{
    QString qstr = QString::fromStdString(playlist.tracks[getIndex()].getName());
     ui->currentSong_2->setText(qstr);
}

void MainWindow::on_textEditNote_textChanged()
{
    const int MAX_NOTE_SIZE = 200;
    if(ui->textEditNote->hasFocus())
        if (ui->textEditNote->toPlainText().length() > MAX_NOTE_SIZE)
        {
            ui->error_message_label->setText("Достигнут предел длины текста");
            QString edT = ui->textEditNote->toPlainText();
            edT.chop(ui->textEditNote->toPlainText().length() - MAX_NOTE_SIZE);
            ui->textEditNote->setText(edT);

            QTextCursor cursor(ui->textEditNote->textCursor());
            cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
            ui->textEditNote->setTextCursor(cursor);
        } else {
            if (ui->textEditNote->toPlainText().length() == MAX_NOTE_SIZE)
                 ui->error_message_label->setText("Достигнут предел длины текста");
            else
                ui->error_message_label->setText("");
        }

}
