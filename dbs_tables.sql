CREATE TABLE Albums (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	title VARCHAR(512),
	album_art_location VARCHAR(2048)
);

CREATE TABLE Songs (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	title VARCHAR(512),
	track_number INTEGER,
	disc_number INTEGER,
	rating SMALLINT DEFAULT 0,
	album_id INTEGER,
	location VARCHAR(2048),
	FOREIGN KEY (album_id) REFERENCES Albums(id)
);

CREATE TABLE Artists (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(512),
	description VARCHAR(1024),
	photo_location VARCHAR(2048)
);

CREATE TABLE Genres (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	name VARCHAR(128)
);

CREATE TABLE ContributingArtists (
	song_id INTEGER,
	artist_id INTEGER,
	PRIMARY KEY (song_id, artist_id),
	FOREIGN KEY (song_id) REFERENCES Songs(id),
	FOREIGN KEY (artist_id) REFERENCES Artists(id)
);

CREATE TABLE AlbumArtists (
	album_id INTEGER,
	artist_id INTEGER,
	PRIMARY KEY (album_id, artist_id),
	FOREIGN KEY (album_id) REFERENCES Albums(id),
	FOREIGN KEY (artist_id) REFERENCES Artists(id)
);

CREATE TABLE SongGenreMap (
	song_id INTEGER,
	genre_id INTEGER,
	PRIMARY KEY (song_id, genre_id),
	FOREIGN KEY (song_id) REFERENCES Songs(id),
	FOREIGN KEY (genre_id) REFERENCES Genres(id)
);

CREATE TABLE Playlists (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	title VARCHAR(512)
);

CREATE TABLE PlaylistSongs (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	playlist_id INTEGER,
	song_id INTEGER,
	FOREIGN KEY (playlist_id) REFERENCES Playlists(id),
	FOREIGN KEY (song_id) REFERENCES Songs(id)
);

INSERT INTO Albums (title, album_art_location) VALUES
("Tiger Zinda Hai", "1.jpg"),
("Dabangg", "2.jpg"),
("From The Fires", "3.jpg");

INSERT INTO Songs (title, track_number, disc_number, album_id, location) VALUES
("Dil Diyan Gallan", 2, 1, 1, "C:\Users\Debasish Bordoloi\Music\MusicBee\Music\Vishal–Shekhar & Julius Packiam\Tiger Zinda Hai\1-02 Dil Diyan Gallan.flac"),
("Tere Mast Mast Do Nain", 1, 1, 2, "C:\Users\Debasish Bordoloi\Music\MusicBee\Music\Sajid-Wajid\Dabangg\1-01 Tere Mast Mast Do Nain.flac"),
("Chori Kiya Re Jiya", 3, 1, 2, "C:\Users\Debasish Bordoloi\Music\MusicBee\Music\Sajid-Wajid\Dabangg\1-03 Chori Kiya Re Jiya.flac"),
("Safari Song", 1, 1, 3, "C:\Users\Debasish Bordoloi\Music\MusicBee\Music\Greta Van Fleet\From The Fires\1-01 Safari Song.flac"),
("Highway Tune", 5, 1, 3, "C:\Users\Debasish Bordoloi\Music\MusicBee\Music\Greta Van Fleet\From The Fires\1-05 Highway Tune.flac");

INSERT INTO Artists (name) VALUES
("Greta Van Fleet"),
("Sajid-Wajid"),
("Rahat Fateh Ali Khan"),
("Sonu Nigam"),
("Shreya Ghoshal"),
("Vishal-Shekhar"),
("Julius Packiam"),
("Atif Aslam");

INSERT INTO ContributingArtists (song_id, artist_id) VALUES 
(1, 8),
(2, 3),
(3, 4),
(3, 5),
(4, 1),
(5, 1);

INSERT INTO AlbumArtists (album_id, artist_id) VALUES
(1, 6),
(1, 7),
(2, 2),
(3, 1);

INSERT INTO Genres (name) VALUES
("Bolywood"),
("Rock");

INSERT INTO SongGenreMap (song_id, genre_id) VALUES
(1, 1),
(2, 1),
(3, 1),
(4, 2),
(5, 2);

INSERT INTO Playlists (title) VALUES
("Test Playlist");

INSERT INTO PlaylistSongs (playlist_id, song_id) VALUES
(1, 3),
(1, 4);