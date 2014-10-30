#include "stdafx.h"
#include "windows.h"
#include "stdhdr.h"
#include "cpsound.h"

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

CPSoundList::CPSoundList(int numSounds)
{
    mSoundTally = 0;
    mNumSounds = numSounds;
#ifdef USE_SH_POOLS
    mpSoundArray = (CPSoundIndex *)MemAllocPtr(gCockMemPool, sizeof(CPSoundIndex) * mNumSounds, FALSE);
#else
    mpSoundArray = new CPSoundIndex[mNumSounds];
#endif
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

CPSoundList::~CPSoundList()
{

    delete [] mpSoundArray;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

int CPSoundList::GetSoundIndex(int id)
{

    int returnEntry = 0;
    int i = 0;
    BOOL found = FALSE;

    while ( not found and i < mSoundTally)
    {

        if (mpSoundArray[i].soundId == id)
        {
            found = TRUE;
            returnEntry = mpSoundArray[i].F4SoundEntry;
        }
        else
        {
            i++;
        }
    }

    F4Assert(found);
    return returnEntry;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

void CPSoundList::AddSound(int id, int entry)
{

    F4Assert(mSoundTally <= mNumSounds - 1); // If we haven't allocated enough
    // space Assert before attempting to
    // add an entry that will scribble.
    mpSoundArray[mSoundTally].soundId = id;
    mpSoundArray[mSoundTally].F4SoundEntry = entry;

    mSoundTally++;
}
