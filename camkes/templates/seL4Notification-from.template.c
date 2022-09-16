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


/*- set notifications = [] -*/
/*- for index in six.moves.range(len(me.parent.to_ends)) -*/
  /*- set end = me.parent.to_ends[index] -*/
  /*- set global_name = '%s_%d_sgi' % (me.parent.name, index) -*/
  /*- set node_name = render_state.label_node_map[end.instance.name] -*/
  /*- set node_id = configuration[node_name]["node_id"] -*/
  /*- set sgi = 32 -*/
    /*- if global_name not in render_state.global_obj_space -*/
        /*- set sgi = render_state.nodes[node_name].sgi_count -*/
        /*- do render_state.nodes[node_name].__setattr__('sgi', sgi + 1) -*/
        /*- do render_state.global_obj_space.__setitem__(global_name, sgi) -*/
    /*- else -*/
        /*- set paddr = render_state.global_obj_space[global_name] -*/
    /*- endif -*/

  /*- do notifications.append((alloc('sgi_%d' % index, seL4_ARM_SGI_Signal, irqs=2**sgi, targets=2**node_id), sgi , node_id)) -*/
/*- endfor -*/


void /*? me.interface.name ?*/_emit_underlying(void) {
    /*- for (notification, sgi, node_id) in notifications -*/
    seL4_ARM_SGI_Signal_Generate(/*? notification ?*/, /*? sgi ?*/, 1lu <<(/*? node_id ?*/));
    /*- endfor -*/
}

/*- else -*/

/*- set notifications = [] -*/
/*- for index in six.moves.range(len(me.parent.to_ends)) -*/
  /*- do notifications.append(alloc('notification_%d' % index, seL4_NotificationObject, write=True)) -*/
/*- endfor -*/

void /*? me.interface.name ?*/_emit_underlying(void) {
    /*- for notification in notifications -*/
    seL4_Signal(/*? notification ?*/);
    /*- endfor -*/
}

/*- endif -*/