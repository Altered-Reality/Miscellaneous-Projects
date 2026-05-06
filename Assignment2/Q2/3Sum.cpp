#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    // Simple bubble sort (no <algorithm>)
    void bubbleSort(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (nums[j] > nums[j + 1]) {
                    int temp = nums[j];
                    nums[j] = nums[j + 1];
                    nums[j + 1] = temp;
                }
            }
        }
    }

    vector<vector<int> > threeSum(vector<int>& nums) {
        vector<vector<int> > result;
        int n = nums.size();

        bubbleSort(nums); // sort manually

        for (int i = 0; i < n - 2; i++) {

            if (i > 0 && nums[i] == nums[i - 1])
                continue; // skip duplicates

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});

                    // skip duplicates
                    int leftVal = nums[left];
                    int rightVal = nums[right];

                    while (left < right && nums[left] == leftVal) left++;
                    while (left < right && nums[right] == rightVal) right--;
                }
                else if (sum < 0) {
                    left++;
                }
                else {
                    right--;
                }
            }
        }

        return result;
    }
};


int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter the numbers:\n";
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    Solution s;
    vector<vector<int> > ans = s.threeSum(nums);

    cout << "\nTriplets that sum to 0:\n";
    if (ans.size() == 0) {
        cout << "None\n";
    } else {
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << "\n";
        }
    }

    return 0;
}