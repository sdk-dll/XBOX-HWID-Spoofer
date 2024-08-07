﻿#include <iostream>
#include <future>

#include "context/ctx.hpp"

auto main() -> std::int32_t
{
	/* setup async future thread */
	std::future<std::int32_t> entry = std::async(std::launch::async, [&]
	{
		/* load libraries (just in case lol cuz i dont add the libraries to the linker) */
		ctx::libraries->initialize();

		std::wcout << L"[~] XBOX-HWID-Spoofer\n";
		try
		{
			/* kill microsoft apps */
			ctx::process->kill_microsoft_apps();

			/* clean registry */
			ctx::registry->clean();

			/* spoof registry (guid) */
			ctx::registry->spoof_guid();

			/* spoof registry (binary) */
			ctx::registry->spoof_binary();

			/* clean cmdkeys */
			ctx::credentials->clean();

			/* apply telemetry filters */
			ctx::network->apply_hosts_filter();

			/* spoof mac address */
			ctx::network->spoof_adapters();

			/* flush dns */
			ctx::network->flush_dns_cache();

			/* restart winmgmt */
			ctx::network->restart_winmgmt();

			/* restart network adapters */
			ctx::network->restart_adapters();
		}
		catch (const std::runtime_error& error)
		{
			std::wcout << L"\n\n[!] fatal error : " << error.what() << L"\n";
			std::wcin.get();
			return EXIT_FAILURE;
		}

		std::wcout << L"\n[~] finalized";
		std::wcin.get();
		return EXIT_SUCCESS;
	});

	return entry.get();
}
