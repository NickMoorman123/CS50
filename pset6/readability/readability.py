
paragraph = input("Text: ")
num_lett = 0
num_word = 1
num_sen = 0

for i in range(0, len(paragraph)):
    if (ord(paragraph[i]) >= ord("a") and ord(paragraph[i]) <= ord("z")) or (ord(paragraph[i]) >= ord("A") and ord(paragraph[i]) <= ord("Z")):
        num_lett += 1
    elif paragraph[i] == " ":
        num_word += 1
    elif paragraph[i] == "." or paragraph[i] == "!" or paragraph[i] == "?":
        num_sen += 1

grade = 5.88 * (num_lett / num_word) - 29.6 * (num_sen / num_word) - 15.3


if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {int(grade)}")