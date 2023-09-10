This hack similar to Sme's ItemSpecificWTA lets you define arbitrary weapon triangle interactions but instead of Item vs Item it's Item vs Type. So you can have a bow with WTA against all Swords.

This has pretty straight foward installation and usage.

Installation
Include ItemTypeWTA.event in free space and add then ItemTypeWTA to the skill system WTA calc loop to install.

Usage
Pick an item ID and an item type. Next configure the change in Hit/Attack. You can set this independent of your actual weapon triangle though so unless thats your intention don't forget to change this if you edit WT values.
