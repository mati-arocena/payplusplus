import csv
import random
import string

ROWS_TO_GENERATE = 1000000
OUTPUT_FILE = "../data/stress_test.csv"


def generate_random_string(length=8):
    return ''.join(random.choices(string.ascii_letters, k=length)).lower()


def generate_seniority_list():
    if random.random() > 0.9:
        return ["None"]
    return [generate_random_string(2) for _ in range(random.randint(3, 6))]


def generate_random_data(num_rows):
    data = set()

    while len(data) < num_rows:
        department = generate_random_string()
        seniority_list = generate_seniority_list()
        
        for seniority in seniority_list:
            if len(data) >= num_rows:
                break
            salary = random.randint(500, 10000)
            increment_percentage = round(random.uniform(0.01, 1.00), 3)
            employee_count = random.randint(1, 1000)
            data.add((department, seniority, salary, increment_percentage, employee_count))
    
    return data


def save_to_csv(data, filename="generated_data.csv"):
    with open(filename, "w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["Department", "Seniority", "Salary", "IncrementPercentage", "EmployeeCount"])
        writer.writerows(data)


if __name__ == "__main__":
    generated_data = generate_random_data(ROWS_TO_GENERATE)
    save_to_csv(generated_data, OUTPUT_FILE)
    print(f"CSV file '{OUTPUT_FILE}' generated with {len(generated_data)} rows.")
