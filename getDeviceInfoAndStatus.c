/////////////////////////////////////////////////////////////////////
// Start Script (PicoC)
//
// V-ZUG HTTP Integration, 22.03.2021
//
// JSON Sample from HTTP GET
// {"DeviceName":"Adora SL","Serial":"00000 000000","Inactive":"true","Program":"","Status":"","ProgramEnd":{"End":"","EndType":"0"},"deviceUuid":"0000000000"}
//
/////////////////////////////////////////////////////////////////////

// Params (virtueller Texteingang mit IP-Adresse als Standardtext z.B. 192.168.1.101)
char ip[15];
ip = getinputtext(0);

// Init
char* returnValue;
char* leftValue;
char deviceValue[1];
int nextQuotes;
int i;

// Loop the whole time
while(TRUE)
{
	// Start
	setlogtext("Wait for 20s");
	sleeps(20);

	// HTTP GET
	returnValue = httpget(ip,"/ai?command=getDeviceStatus");
	
	// Pruefe HTTP GET Resultat
	if (strlen(returnValue) == 0)
	{
		setlogtext("HTTP GET fehlgeschlagen");
		setlogtext("returnValue: leer");
	}
	else
	{
		setlogtext("HTTP GET erfolgreich");
		setlogtext(returnValue);

		// Loop trough values
		i = 1;
		while(i < 8)
		{
			if ( i > 1 )
			{
				returnValue = leftValue;
			}
			leftValue = strstrskip(returnValue,"\":\"");
			nextQuotes = strfind(leftValue,"\"",0);
			strncpy(deviceValue,leftValue,nextQuotes);

			// Pruefe HTTP GET Resultat
			if ( 0 > 1 )
			{
				setlogtext("Device-Wert konnte nicht ermittelt werden");
				setlogtext("deviceValue: leer");
			}
			else
			{
				printf("Integer: %d\n", i);
				setlogtext(deviceValue);
    			if ( i == 1 )
				{
					// setoutputtext(0,deviceValue); // Gerätename
				}
				if ( i == 2 )
				{
					// setoutput(0,deviceValue); // Seriennummer
				}
				if ( i == 3 )
				{
					// strcmp (String Compare) können wir zwei Strings vergleichen.
					// Der Rückgabewert kann hierbei folgende Werte haben: 0 die Strings sind gleich
					// Wenn "deviceValue = false", dann 0 und somit weiter mit "else"
					if ( strcmp(deviceValue , "false" ) )
					{
						setoutput(0,0); // Inaktiv = true
					}
					else
					{
						setoutput(0,1); // Inaktiv = false
					}
				}
				if ( i == 4 )
				{
					setoutputtext(0,deviceValue); // Programm (Vorspühlen)
				}
				if ( i == 5 )
				{
					setoutputtext(1,deviceValue); // Status (Start in 0h26)
				}
				if ( i == 6 )
				{
					setoutputtext(2,deviceValue); // Ende (0h37)
				}
				if ( i == 7 )
				{
					int deviceValueInt = atoi(deviceValue);
    				printf("deviceValueInt : %d\n", deviceValueInt);
					setoutput(1,deviceValueInt); // EndeTyp
				}
				// 8 = deviceUUID

				// Speicher pro Wert leeren
				// free(deviceValue); // --> Crash wenn diese aktiviert werden
				
				i++;
			}
		}
	}

	// Gesmat-Speicher leeren
	// free(returnValue); // --> Crash wenn diese aktiviert werden
	// free(leftValue); // --> Crash wenn diese aktiviert werden

	// Ende
	setlogtext("Go to sleep for 40s");
	sleeps(40);
}
