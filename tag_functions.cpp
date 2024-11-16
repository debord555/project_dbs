#include "tag_functions.hpp"
#include "misc.hpp"

#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/tpropertymap.h>

/**
 * @brief Gets metadata from a music file.
 *
 * @details This function returns a Metadata struct containing title, contributing
 *          artists, album, album artists, genres, track number, disc number, and
 *          file location. Returns the data in UTF-8 encoding.
 *
 * @param[in] file_location The path to the music file.
 *
 * @return A Metadata struct containing music metadata.
 */
Metadata getMetadata(std::string file_location) {
    TagLib::FileRef file_ref(file_location.c_str());
    TagLib::Tag *file_tag = file_ref.tag();
    TagLib::PropertyMap props = file_ref.properties();
    Metadata metadata;
    metadata.file_location = file_location;
    metadata.title = file_tag->title().to8Bit(true);
    metadata.contributing_artists = splitString(file_tag->artist().to8Bit(true));
    metadata.album = file_tag->album().to8Bit(true);
    metadata.album_artists = splitString(props["ALBUMARTIST"].toString().to8Bit(true));
    metadata.genres = splitString(file_tag->genre().to8Bit(true));
    metadata.track_number = file_tag->track();
    metadata.disc_number = props["DISCNUMBER"].toString().toInt();
    metadata.year = file_tag->year();
    return metadata;
}

std::ostream &operator<<(std::ostream &s, const Metadata &m) {
    s << "File Location: " << m.file_location << std::endl;
    s << "Title: " << m.title << std::endl;
    s << "Contributing Artists: ";
    for (auto &artist : m.contributing_artists)
        s << artist << ", ";
    s << std::endl;
    s << "Album: " << m.album << std::endl;
    s << "Album Artists: ";
    for (auto &artist : m.album_artists)
        s << artist << ", ";
    s << std::endl;
    s << "Genres: ";
    for (auto &genre : m.genres)
        s << genre << ", ";
    s << std::endl;
    s << "Track Number: " << m.track_number << std::endl;
    s << "Disc Number: " << m.disc_number << std::endl;
    s << "Year: " << m.year << std::endl;
    return s;
}


