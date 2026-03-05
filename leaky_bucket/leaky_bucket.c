#include<stdio.h>

int main()
{
    int b_size, n, rate;

    // Input the maximum bucket capacity
    printf("Enter the bucket size : ");
    scanf("%d",&b_size);

    // Input the outgoing rate (how many packets leave per unit time)
    printf("Enter the output rate : ");
    scanf("%d",&rate);

    // Number of incoming packets
    printf("Enter the number of incoming packets : ");
    scanf("%d",&n);

    int store = 0, inc;  
    // store = current packets inside the bucket
    // inc = incoming packet size

    // Loop runs until all packets are processed
    while(n != 0)
    {
        // Input incoming packet size
        printf("Enter the packet size : ");
        scanf("%d",&inc);

        // Check if bucket has enough space
        if(inc <= b_size - store)
        {
            // Add packet to bucket
            store += inc;

            printf("Used space of bucket is %d/%d\n",store,b_size);
        }
        else
        {
            // If packet exceeds remaining space, drop extra packets
            printf("Bucket is full. Discarded packets: %d\n",
                   (inc - (b_size - store)));

            // Fill bucket to maximum capacity
            store = b_size;
        }

        // Packets leave the bucket at a fixed rate
        store -= rate;

        // Prevent negative buffer value
        if(store < 0)
            store = 0;

        // Reduce number of inputs
        n--;
    }
}
