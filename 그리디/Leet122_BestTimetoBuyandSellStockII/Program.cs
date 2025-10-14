Solution s = new Solution();
Console.WriteLine(s.MaxProfit(new int[] {7, 1, 5, 3, 6, 4}));
Console.WriteLine(s.MaxProfit(new int[] { 1, 2, 3, 4, 5 }));
Console.WriteLine(s.MaxProfit(new int[] { 7, 6, 4, 3, 1 }));

public class Solution
{
    public int MaxProfit(int[] prices)
    {
        int money = 0;
        for (int i = 0; i < prices.Length - 1; i++)
        {
            if (prices[i] < prices[i + 1])
            {
                money -= prices[i];
                money += prices[i + 1];
            }
        }

        return money;
    }
}

