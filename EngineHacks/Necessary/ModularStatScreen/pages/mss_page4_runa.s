.thumb
.include "mss_defs.s"

.global MSS_page4
.type MSS_page4, %function


MSS_page4:

page_start



@ Next let's draw Gaiden spells if the hack is installed.
draw_gaiden_spells_at 13, 3, GaidenStatScreen @ GaidenStatScreen is a pointer to the routine, GaidenStatScreen.

page_end

.align
.ltorg
