#include "DJLibraryService.h"
#include "SessionFileParser.h"
#include "MP3Track.h"
#include "WAVTrack.h"
#include <iostream>
#include <memory>
#include <filesystem>
#include <algorithm>


DJLibraryService::DJLibraryService(const Playlist& playlist) 
    : playlist(playlist), library() {}


DJLibraryService::~DJLibraryService()
{
    for (AudioTrack *track : library)
    {
        delete track;
    }
    library.clear();
}
/**
 * @brief Load a playlist from track indices referencing the library
 * @param library_tracks Vector of track info from config
 */
void DJLibraryService::buildLibrary(const std::vector<SessionConfig::TrackInfo>& library_tracks) {
    //Todo: Implement buildLibrary method
    //std::cout << "TODO: Implement DJLibraryService::buildLibrary method\n"<< library_tracks.size() << " tracks to be loaded into library.\n";
    for (const SessionConfig::TrackInfo &info : library_tracks)
    {
        if (info.type == "MP3")
        {
            AudioTrack *mp3tr = new MP3Track(info.title, info.artists, info.duration_seconds,
                                             info.bpm, info.extra_param1, info.extra_param2);
            // std::cout << "MP3Track created: " << info.extra_param1 << " kbps\n";
            library.push_back(mp3tr);
        }
        else if (info.type == "WAV")
        {
            AudioTrack *wavtr = new WAVTrack(info.title, info.artists, info.duration_seconds,
                                             info.bpm, info.extra_param1, info.extra_param2);
            // std::cout << "WAVTrack created: " << info.extra_param1 << "Hz/" << info.extra_param2 << "bit\n";
            library.push_back(wavtr);
        }
    }
    std::cout << "[INFO] Track library built: " << library_tracks.size() << " tracks loaded\n";

}

/**
 * @brief Display the current state of the DJ library playlist
 * 
 */
void DJLibraryService::displayLibrary() const {
    std::cout << "=== DJ Library Playlist: " 
              << playlist.get_name() << " ===" << std::endl;

    if (playlist.is_empty()) {
        std::cout << "[INFO] Playlist is empty.\n";
        return;
    }

    // Let Playlist handle printing all track info
    playlist.display();

    std::cout << "Total duration: " << playlist.get_total_duration() << " seconds" << std::endl;
}

/**
 * @brief Get a reference to the current playlist
 * 
 * @return Playlist& 
 */
Playlist& DJLibraryService::getPlaylist() {
    // Your implementation here
    return playlist;
}

/**
 * TODO: Implement findTrack method
 * 
 * HINT: Leverage Playlist's find_track method
 */
AudioTrack* DJLibraryService::findTrack(const std::string& track_title) {
    // Your implementation here
    return playlist.find_track(track_title);
}

void DJLibraryService::loadPlaylistFromIndices(const std::string& playlist_name, 
                                               const std::vector<int>& track_indices) {
    // Your implementation here
    std::cout << "[INFO] Loading playlist: " << playlist_name << "\n";
    playlist = Playlist(playlist_name);
    int added_count = 0;

    for (int ind : track_indices)
    {
        if (ind < 1 || static_cast<size_t>(ind) > library.size())
        {
            std::cout << "[WARNING] Invalid track index: " << ind << "\n";
            continue;
        }

        AudioTrack *track = library[ind - 1];
        PointerWrapper<AudioTrack> cloned = track->clone();

        if (!cloned)
        {
            std::cout << "[ERROR] Track: \"" << track->get_title() << "\" failed to clone\n";
            continue;
        }
        
        AudioTrack *cloned_raw = cloned.get();

        cloned_raw->load();
        cloned_raw->analyze_beatgrid();
        playlist.add_track(cloned.release());
        added_count++;

        // std::cout << "Added '" << track->get_title() << "' to playlist '" << playlist_name << "'\n";
    }

    std::cout << "[INFO] Playlist loaded: " << playlist_name << " (" << added_count << " tracks)\n";

    // // For now, add a placeholder to fix the linker error
    // (void)playlist_name;  // Suppress unused parameter warning
    // (void)track_indices;  // Suppress unused parameter warning
}
/**
 * TODO: Implement getTrackTitles method
 * @return Vector of track titles in the playlist
 */
std::vector<std::string> DJLibraryService::getTrackTitles() const {
    // Your implementation here
    std::vector<std::string> titles;
    for (AudioTrack *tr : playlist.getTracks())
    {
        titles.push_back(tr->get_title());
    }
    std::reverse(titles.begin(), titles.end());
    return titles; // Placeholder
}
