#include "DJControllerService.h"
#include "MP3Track.h"
#include "WAVTrack.h"
#include <iostream>
#include <memory>

DJControllerService::DJControllerService(size_t cache_size)
    : cache(cache_size) {}
/**
 * TODO: Implement loadTrackToCache method
 */
<<<<<<< HEAD
int DJControllerService::loadTrackToCache(AudioTrack &track)
{
    // Your implementation here

=======
int DJControllerService::loadTrackToCache(AudioTrack& track) {
    // Your implementation here 
>>>>>>> origin/new_branch
    if (cache.contains(track.get_title()))
    {
        cache.get(track.get_title());
        return 1;
    }

    PointerWrapper<AudioTrack> cloned = track.clone();
    if (!cloned)
    {
        std::cout << "[ERROR] Track: \"" << track.get_title() << "\" failed to clone\n";
        return -1;
    }

    AudioTrack *raw = cloned.get();

    raw->load();
    raw->analyze_beatgrid();

    bool evicted = cache.put(std::move(cloned));
    if (evicted)
        return -1;
    else
        return 0; // Placeholder
}

void DJControllerService::set_cache_size(size_t new_size)
{
    cache.set_capacity(new_size);
}
// implemented
void DJControllerService::displayCacheStatus() const
{
    std::cout << "\n=== Cache Status ===\n";
    cache.displayStatus();
    std::cout << "====================\n";
}

/**
 * TODO: Implement getTrackFromCache method
 */
AudioTrack *DJControllerService::getTrackFromCache(const std::string &track_title)
{
    // Your implementation here
<<<<<<< HEAD

=======
>>>>>>> origin/new_branch
    AudioTrack *raw = cache.get(track_title);
    if (raw != nullptr)
        return raw;

    return nullptr; // Placeholder
}
