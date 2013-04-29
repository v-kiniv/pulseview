/*
 * This file is part of the PulseView project.
 *
 * Copyright (C) 2013 Joel Holdsworth <joel@airwebreathe.org.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef PULSEVIEW_PV_DEVICEMANAGER_H
#define PULSEVIEW_PV_DEVICEMANAGER_H

#include <glib.h>

#include <list>
#include <string>

struct sr_context;
struct sr_dev_driver;
struct sr_dev_inst;

namespace pv {

class DeviceManager
{
public:
	DeviceManager(struct sr_context *sr_ctx);

	~DeviceManager();

	const std::list<sr_dev_inst*>& devices() const;

	std::list<sr_dev_inst*> driver_scan(
		struct sr_dev_driver *const driver,
		GSList *const drvopts = NULL);

	static std::string format_device_title(const sr_dev_inst *const sdi);

private:
	void init_drivers();

	static void release_devices();

	void scan_all_drivers();

	static bool compare_devices(const sr_dev_inst *const a,
		const sr_dev_inst *const b);

private:
	struct sr_context *const _sr_ctx;
	std::list<sr_dev_inst*> _devices;
};

} // namespace pv

#endif // PULSEVIEW_PV_DEVICEMANAGER_H
