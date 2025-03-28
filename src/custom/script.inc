// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Script Commands
 * Place the body of custom script commands in this file.
 * Format:
 *	BUILDIN_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//BUILDIN_FUNC(example)
//{
//	ShowInfo("buildin_example: It works!\n");
//	script_pushint(st,1);
//	return 0;
//}

/** [Cydh]
* Get security status of player
* is_security {<char_id>};
* @return sd->state.security
*/
BUILDIN_FUNC(is_security) {
	struct map_session_data* sd;

	if (script_hasdata(st,2))
		sd = map_charid2sd(script_getnum(st,2));
	else
		script_rid2sd(sd);

	if (sd == NULL) {
		ShowError("buildin_is_security: Failed to check player's security state, no player attached!\n");
		script_pushint(st,-1);
		return SCRIPT_CMD_FAILURE;
	}
	script_pushint(st,sd->state.security);
	return SCRIPT_CMD_SUCCESS;
}

/** [Cydh]
* Set security status of player
* setsecurity <status>{,<char_id>};
* @param status 1 : enable. 0 : disable
*/
BUILDIN_FUNC(setsecurity) {
	struct map_session_data* sd;

	if (script_hasdata(st,3))
		sd = map_charid2sd(script_getnum(st,3));
	else
		script_rid2sd(sd);

	if (sd == NULL) {
		ShowError("buildin_setsecurity: Failed to check player's security state, no player attached!\n");
		script_pushint(st,-1);
		return SCRIPT_CMD_FAILURE;
	}

	switch (script_getnum(st,2)) {
		case 1:
			sd->state.security = 1;
			clif_displaymessage(sd->fd,"Security is enabled!");
			break;
		default:
			sd->state.security = 0;
			clif_displaymessage(sd->fd,"Security is disabled!");
			break;
	}

	script_pushint(st,1);
	return SCRIPT_CMD_SUCCESS;
}