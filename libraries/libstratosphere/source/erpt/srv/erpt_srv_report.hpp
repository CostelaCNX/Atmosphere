/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <stratosphere.hpp>
#include "erpt_srv_allocator.hpp"
#include "erpt_srv_stream.hpp"
#include "erpt_srv_journal.hpp"

namespace ams::erpt::srv {

    enum ReportOpenType {
        ReportOpenType_Create = 0,
        ReportOpenType_Read   = 1,
    };

    constexpr inline u32 ReportStreamBufferSize = 1_KB;

    class Report : public Allocator, public Stream {
        private:
            JournalRecord<ReportInfo> *m_record;
            bool m_redirect_to_sd_card;
        private:
            ReportFileName FileName() const;
            void CloseStream();
        public:
            static ReportFileName FileName(ReportId report_id, bool redirect_to_sd = false);
        public:
            explicit Report(JournalRecord<ReportInfo> *r, bool redirect_to_sd = false);
            ~Report();

            Result Open(ReportOpenType type);
            Result Read(u32 *out_read_count, u8 *dst, u32 dst_size);
            Result Delete();
            void Close();

            Result GetFlags(ReportFlagSet *out) const;
            Result SetFlags(ReportFlagSet flags);
            Result GetSize(s64 *out) const;

            template<typename T>
            Result Write(T val) {
                (void)val;
                R_SUCCEED();
            }

            template<typename T>
            Result Write(const T *buf, u32 buffer_size) {
                (void)buf;
                (void)buffer_size;
                R_SUCCEED();
            }
    };

}