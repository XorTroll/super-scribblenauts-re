# Objectnaut

**Objectnaut** is the (official) name of the object/adjective system used in the Scribblenauts saga. The name can be found in [interviews given by the game developers](https://en.wikipedia.org/wiki/Scribblenauts_(video_game)#Engine) or in debug symbols found in Scribblenauts Remix.

> TODO: overall description, similarities/differences between games...

## Game differences

- In Super, internal buffers for text input/etc have a size of `128` characters, while this size is `256` in Remix.

## Details

### Temperature system

The temperature system is fairly limited.

The only objects making use of the [*SetTemperature* action](object.md) are kitchen appliances (microwaves, ovens and so on) and are only used to heat. Food/objects are only frozen by literally using the `FROZEN` adjective.

### Triggers

*OnCatchFire* is only checked by `VOODOO DOLL`.

*OnSplit* is only checked by `BEAVER`.

## Unused features

### Triggers

The following triggers are never used by objects:

- *OnObjectSwap*

- *OnAttached*

- *OnDetached*

- *OnPhysicsRest*

- *ConditionAnd*

- *ConditionOr*

- *OnCheckVariable*

- *OnUpdate*

- *OnContained*

- *OnUncontained*

- *OnObjectAdded*

- *OnAiState*

- *OnObjectCountInArea*

- *OnVelocity*

- *OnHearSound*

- *TriggerGroup*

- *ConditionOiAnd*

- *OnAiUnequip*

- *OnExtinguishFire*

- *OnKickAdjective*

### Actions

The following actions are never used by objects:

- *MoveTo*

- *MoveRelative*

- *AttachTo*ShowNotepad

- *DetachFromAll*

- *SetVariable*

- *SpawnObjectAt*

- *Cinematic*

- *ShowNotepad*

- *EncaseInIce*

- *SetStageObject*

- *EnableEntity*

- *EnableSFAnim*

- *RotateEntity*

- *ShowFeedback*

- *Lock*

- *SetInterruptFlag*

- *Untouchable*

- *ModifyLineOfSight*
