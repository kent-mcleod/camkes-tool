/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <sel4/sel4.h>

/*? macros.show_includes(me.instance.type.includes) ?*/

/*- set nodes = set() -*/
/*- for end in me.parent.from_ends -*/
    /*- do nodes.add(render_state.label_node_map[end.instance.name]) -*/
/*- endfor -*/

/*- for end in me.parent.to_ends -*/
    /*- do nodes.add(render_state.label_node_map[end.instance.name]) -*/
/*- endfor -*/

/*- set multicore = len(nodes) > 1 -*/
    
/*- if multicore -*/



/*- set end = me.parent.to_end -*/
/*- set global_name = '%s_%d_sgi' % (me.parent.name, 0) -*/
/*- set node_name = render_state.label_node_map[end.instance.name] -*/
/*- set node_id = configuration[node_name]["node_id"] -*/
/*- set sgi = 32 -*/
/*- if global_name not in render_state.global_obj_space -*/
    /*- set sgi = render_state.nodes[node_name].sgi_count -*/
    /*- do render_state.nodes[node_name].__setattr__('sgi_count', sgi + 1) -*/
    /*- do render_state.global_obj_space.__setitem__(global_name, sgi) -*/
/*- else -*/
    /*- set sgi = render_state.global_obj_space[global_name] -*/
/*- endif -*/

/*- set notification = alloc(global_name, seL4_ARM_SGI_Signal, irqs=2**sgi, targets=2**node_id) -*/


void /*? me.interface.name ?*/_emit_underlying(void) {
    seL4_ARM_SGI_Signal_Generate(/*? notification ?*/, /*? sgi ?*/, 1lu <<(/*? node_id ?*/));
}

/*- else -*/


/*# This value is completely arbitrary as long as it matches the one in the
 *# template for the other side of this connector.
 #*/
/*- set badge_magic = int('0xbad1dea', 16) -*/

/*- set notification = alloc('notification', seL4_NotificationObject, write=True) -*/
/*- do cap_space.cnode[notification].set_badge(badge_magic) -*/

void /*? me.interface.name ?*/_emit_underlying(void) {
    seL4_Signal(/*? notification ?*/);
}

/*- endif -*/