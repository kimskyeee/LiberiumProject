# Game Structure Document

## 1. Game Overview
- Genre: 2D Side-scrolling, Single-player
- Core Loop: Town → Quest → Battle/Mini-game → Reward → Return
- Theme: World turning into paper (Paperization)
- All Contents have their own manager (ex: QuestManager, ItemManager...)
- UI System - MVVM
- Use CMS Data

------------------------------------------------------------------------

## 2. Core Systems

### Movement
- Paper 2D character
- Player controls left/right/up/down movement
- but left/right anim only
- Camera follows with margin system

### Map & Portal
- Hub-based structure (Town)
- Portal-based movement between locations

### Inventory
- Item storage with stack system
- Gold management

### Quest System
- Accept → Progress → Complete → Reward
- Objective-based tracking

### Combat
- Turn-based system
- Player vs Enemy loop

### Minigame
- Command input based minigame
- Reward on success

------------------------------------------------------------------------

## 3. MVP Scope
- 1 Town
- 1 Dungeon
- 1 Minigame
- 1 Boss
- 3~5 Quests
