#include <stdio.h>
struct Result {
    int start;
    int end;
    int sum;
};
struct Result MaxCrossingSubarray(int arr[], int low, int mid, int high)
{
    int left_sum = -99999;
    int sum = 0;
    int max_left = mid;
    for (int i = mid; i >= low; i--) {
        sum += arr[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }
    int right_sum = -99999;
    sum = 0;
    int max_right = mid + 1;
    for (int j = mid + 1; j <= high; j++) {
        sum += arr[j];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = j;
        }
    }
    struct Result res = {max_left, max_right, left_sum + right_sum};
    return res;
}
struct Result MaxSubarray(int arr[], int low, int high) {
    if (low == high) {
        struct Result base = {low, high, arr[low]};
        return base;
    }
    int mid = (low + high) / 2;
    struct Result left = MaxSubarray(arr, low, mid);
    struct Result right = MaxSubarray(arr, mid + 1, high);
    struct Result cross = MaxCrossingSubarray(arr, low, mid, high);
    if (left.sum > right.sum && left.sum > cross.sum)
        return left;
    else if (right.sum > left.sum && right.sum > cross.sum)
        return right;
    else
        return cross;
}
int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    int resource[n];
    printf("Enter resource values for %d tasks:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &resource[i]);
    }
    struct Result result = MaxSubarray(resource, 0, n - 1);
    printf("Maximum resource utilization is %d\n", result.sum);
    printf("From task %d to task %d", result.start, result.end);
    return 0;
}
