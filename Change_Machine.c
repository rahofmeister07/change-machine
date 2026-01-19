#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/* Create table of common US denominations in cents */
int common_us_denomination[] = { 10000, 5000, 2000, 1000, 500, 100, 25, 10, 5, 1 };

/* Calculates and returns amount of a specific US denomination to dispense */
int calculate_dispense_amount(int* remainder, int denomination);

int main (void)
{
	int run_again = 1;
	float money_entered = 0.0f;
	int money_remaining = 0;
	int read_scan = 0;

	while (run_again)
	{
		/* Prompt user to enter money into the change machine & store the value */
		/* Input validation would need to be more robust for production */
		do
		{
			printf("Please enter money into the change machine: $");
			read_scan = scanf("%f", &money_entered);
			while (getchar() != '\n'); // Clear leftover characters from input buffer
		} while (read_scan != 1 || money_entered < 0.01); // Keep prompting user to enter money until they enter a valid amount


		money_remaining = (int)(money_entered * 100.0f);

		/* Traverse table of common US denominations from largest to smallest denomination */
		int number_of_denominations = sizeof(common_us_denomination) / sizeof(common_us_denomination[0]);
		for (int i = 0; i < number_of_denominations; i++)
		{
			int current_denomination = common_us_denomination[i];

			/* Dispense money if the money remaining is greater than the current denomination */
			if (money_remaining >= current_denomination)
			{
				int dispense_amount = calculate_dispense_amount(&money_remaining, current_denomination);

				/* Print the number of bills */
				if (current_denomination >= 100)
				{
					printf("\n$%d: %d", (current_denomination / 100), dispense_amount);
				}

				/* Print the number of coins */
				else
				{
					printf("\n%dc: %d", current_denomination, dispense_amount);
				}
			}
		}
		
		/* Ask user if they would like to run the program again */
		char run;
		printf("\n");

		do
		{	
			printf("\nWould you like to run again (y/n): ");
			read_scan = scanf(" %c", &run); // Space to skip whitespace
			while (getchar() != '\n'); // Clear leftover characters from input buffer
		} while ((run != 'n' && run != 'N' && run != 'y' && run != 'Y') || read_scan != 1); // Keep prompting user to enter money until they enter a valid letter

		if (run == 'n' || run == 'N')
		{
			run_again = 0;
		}

		printf("\n");
	}

	/* Print exit message */
	printf("\nThank You!\n");

	return 0;
}

/* Calculates and returns amount of a specific US denomination to dispense */
int calculate_dispense_amount(int* remainder, int denomination)
{
	/* Count how many bills or coins to dispense */
	int denomination_count = 0;

	/* Keep increasing the amount to dispense until the current denomination is greater than the remaining money */
	while (*remainder >= denomination)
	{
		denomination_count++;
		*remainder -= denomination;
	}

	return denomination_count;
}