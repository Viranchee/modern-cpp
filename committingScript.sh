echo "START"
FC_BRANCH=$(git branch --show-current)
PR_NUM=$(echo $FC_BRANCH | awk -F'Fed/ch' '{print $2}')
N_BRANCH="Fed/ch$(($PR_NUM + 1))"
echo "Current branch: " $FC_BRANCH "\t Next branch: " $N_BRANCH "\t Branch number: " $PR_NUM

read -p "Proceed?" -n 1 -r

gaa
gce
gp
gh pr create  --body "Solved" --base main --title $FC_BRANCH
# gh pr merge -s $PR_NUM
# gco main
# gl
# gco -b $N_BRANCH