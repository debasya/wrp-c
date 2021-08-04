/* SPDX-FileCopyrightText: 2021 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */

#include "test_common.h"

// clang-format off
const struct wrp_string list[3] = {
    { .s = "Partner 1", .len = 9 },
    { .s = "Partner 2", .len = 9 },
    { .s = "Example",   .len = 7 },
};

const struct wrp_nvp meta[3] = {
    { .name.s = "n1", .name.len = 2, .value.s = "v1",  .value.len = 2 },
    { .name.s = "n2", .name.len = 2, .value.s = "12",  .value.len = 2 },
    { .name.s = "n3", .name.len = 2, .value.s = "abc", .value.len = 3 },
};

const struct test_vector test = {
    .wrp_from_msgpack_rv = WRPE_OK,
    .wrp_to_msgpack_rv   = WRPE_OK,
    .wrp_to_string_rv    = WRPE_OK,

    .in.msg_type                  = WRP_MSG_TYPE__EVENT,
    .in.u.event.trans_id.s        = "c07ee5e1-70be-444c-a156-097c767ad8aa",
    .in.u.event.trans_id.len      = 36,
    .in.u.event.source.s          = "source-address",
    .in.u.event.source.len        = 14,
    .in.u.event.dest.s            = "dest-address",
    .in.u.event.dest.len          = 12,
    .in.u.event.partner_ids.count = 3,
    .in.u.event.partner_ids.list  = (struct wrp_string*) list,
    .in.u.event.content_type.s    = "application/json",
    .in.u.event.content_type.len  = 16,
    .in.u.event.payload.data      = (const uint8_t*) "event 1234",
    .in.u.event.payload.len       = 10,
    .in.u.event.metadata.count    = 3,
    .in.u.event.metadata.list     = (struct wrp_nvp*) meta,
 
    .string = "wrp_event_msg {\n"
              "    .trans_id      = 'c07ee5e1-70be-444c-a156-097c767ad8aa'\n"
              "    .source        = 'source-address'\n"
              "    .dest          = 'dest-address'\n"
              "    .partner_ids   = 'Partner 1, Partner 2, Example'\n"
              "    .content_type  = 'application/json'\n"
              "    .payload (len) = 10\n"
              "    .metadata      = {\n"
              "        .n1: 'v1'\n"
              "        .n2: '12'\n"
              "        .n3: 'abc'\n"
              "    }\n"
              "}\n",

    .msgpack_len = 226,
    .msgpack =
        "\x88"  /* 8 name value pairs */
            "\xa8""msg_type"         /* : */ "\x04" // 4
            "\xa6""source"           /* : */ "\xae""source-address"
            "\xa4""dest"             /* : */ "\xac""dest-address"
            "\xab""partner_ids"      /* : */ "\x93" // 3
                                                 "\xa9""Partner 1"
                                                 "\xa9""Partner 2"
                                                 "\xa7""Example"
            "\xa8""metadata"         /* : */ "\x83" // 3
                                                 "\xa2""n1" "\xa2""v1"
                                                 "\xa2""n2" "\xa2""12"
                                                 "\xa2""n3" "\xa3""abc"

            "\xb0""transaction_uuid" /* : */ "\xd9\x24""c07ee5e1-70be-444c-a156-097c767ad8aa"
            "\xac""content_type"     /* : */ "\xb0""application/json"
            "\xa7""payload"          /* : */ "\xc4""\x0a" /* len 10 */
                                             "event 1234"
};
// clang-format on

const char *test_name = __FILE__;
