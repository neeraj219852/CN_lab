#include<stdio.h>

int main()
{
    int inc;        // incoming packet size
    int outg;       // outgoing rate (how many packets leave the bucket each time)
    int b_size;     // maximum bucket size (capacity)
    int n;          // number of inputs (number of packet arrivals)
    int store = 0;  // current packets stored in bucket

    // Taking bucket size, outgoing rate and number of packet inputs
    printf("Enter bucket size, outgoing rate and number of inputs:");
    scanf("%d %d %d",&b_size,&outg,&n);

    // Loop runs for each incoming packet
    while (n != 0)
    {
        // Input packet size
        printf("Enter the incoming packet size :");
        scanf("%d",&inc);

        printf("Incoming packet size :- %d\n",inc);

        // Check if bucket has enough free space
        if (inc <= (b_size - store))
        {
            // If space is available, store the packet
            store += inc;

            printf("Bucket buffer size is %d out of %d\n",store, b_size);
        }
        else
        {
            // If packet exceeds remaining space, drop extra packets
            printf("Dropped number of packets :- %d\n", inc - (b_size - store));

            // Fill the bucket completely
            store += b_size - store;

            printf("Bucket buffer size is %d out of %d\n",store, b_size);
        }

        // Packets leave the bucket at fixed outgoing rate
        store = store - outg;

        // Display packets remaining in bucket
        printf("After outgoing,%d packets left out of %d in buffer\n", store, b_size);

        printf("\n");

        // Decrease number of inputs
        n--;
    }
}