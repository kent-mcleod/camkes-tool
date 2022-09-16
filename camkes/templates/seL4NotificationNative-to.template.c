/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <assert.h>
#include <camkes/tls.h>
#include <sel4/sel4.h>
#include <stdlib.h>

/*? macros.show_includes(me.instance.type.includes) ?*/

/*- set nodes = set() -*/
/*- for end in me.parent.from_ends -*/
    /*- do nodes.add(render_state.label_node_map[end.instance.name]) -*/
/*- endfor -*/

/*- for end in me.parent.to_ends -*/
    /*- do nodes.add(render_state.label_node_map[end.instance.name]) -*/
/*- endfor -*/

/*- set multicore = len(nodes) > 1 -*/


/*# This value is completely arbitrary as long as it matches the one in the
 *# template for the other side of this connector.
 #*/

int /*? me.interface.name ?*/__run(void) {
    return 0;
}

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

/*- set ntfn_obj = alloc_obj('ntfn', seL4_NotificationObject) -*/
/*- set ntfn = alloc_cap('ntfn', ntfn_obj, read=True) -*/
/*- set badge_magic = int('0xbad1dea', 16) -*/
/*- do cap_space.cnode[ntfn].set_badge(badge_magic) -*/

/*- set irq = alloc('irq', seL4_IRQHandler, number=sgi, notification=my_cnode[ntfn]) -*/

int /*? me.interface.name ?*/_poll(void) {
    seL4_Word badge = 0;
    seL4_Poll(/*? ntfn ?*/, &badge);
    if (badge == /*? badge_magic ?*/) {
        seL4_IRQHandler_Ack(/*? irq ?*/);
        return 1;

    }
    return 0;
}

void /*? me.interface.name ?*/_wait(void) {
    seL4_Wait(/*? ntfn ?*/, NULL);
    seL4_IRQHandler_Ack(/*? irq ?*/);
}

/*- else -*/

/*- set badge_magic = int('0xbad1dea', 16) -*/
/*- set notification = alloc('notification', seL4_NotificationObject, read=True) -*/
/*- do cap_space.cnode[notification].set_badge(badge_magic) -*/


int /*? me.interface.name ?*/_poll(void) {
    seL4_Word badge = 0;
    seL4_Poll(/*? notification ?*/, &badge);
    return badge == /*? badge_magic ?*/;
}

void /*? me.interface.name ?*/_wait(void) {
    seL4_Wait(/*? notification ?*/, NULL);
}

/*- endif -*/
