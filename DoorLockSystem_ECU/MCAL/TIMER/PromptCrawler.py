import os


def list_files():

    files = [ f for f in os.listdir('.') if os.path.isfile(f) ]
    
    for idx, file in enumerate(files, start=1):
        print(f"{idx}. {file}")
    
    return files

def display_and_write_file_contents(files, output_file):
    with open(output_file, 'w') as output_file:
        
        for file in files:
            
            output_file.write(f"//Content of {file}\n")

            with open(file, 'r') as f:                
                content = f.read()
                output_file.write(content)
                output_file.write("\n//" + "-"*20 + "\n")
            
    print(f"Content has successfully written to {output_file}")



def get_user_choices(files):
    choices = input("Enter the numbers of the files you want to select, separated by commas: ")
    selected_files = []
    for choice in choices.split(','):
        try:
            idx = int(choice.strip())
            if 1 <= idx <= len(files):
                selected_files.append(files[idx - 1])
            else:
                print(f"Invalid choice: {idx}")
        except ValueError:
            print(f"Invalid input: {choice}")
    return selected_files



if __name__ == "__main__":
    files = list_files()
    selected_files = get_user_choices(files)
    if selected_files:
        output_file = "combined_output.txt"
        display_and_write_file_contents(selected_files, output_file)
    else:
        print("No valid files selected.")
