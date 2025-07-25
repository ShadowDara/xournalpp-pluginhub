import os
import sys
import json
import requests

def get_files_in_pr(repo, pr_number):
    headers = {
        'Accept': 'application/vnd.github.v3+json',
    }
    url = f'https://api.github.com/repos/{repo}/pulls/{pr_number}/files'
    response = requests.get(url, headers=headers)
    if response.status_code == 403:
        print("Rate limit exceeded oder Auth benötigt. Versuch mit Token.")
        sys.exit(1)
    response.raise_for_status()
    files = response.json()

    new_files = [f['filename'] for f in files if f['status'] == 'added']
    modified_files = [f['filename'] for f in files if f['status'] == 'modified']
    return new_files, modified_files

if __name__ == "__main__":
    repo = os.getenv('GITHUB_REPOSITORY')
    pr_number = os.getenv('PR_NUMBER')

    if not (repo and pr_number):
        print("Error: env variables GITHUB_REPOSITORY or PR_NUMBER missing.")
        sys.exit(1)

    new_files, modified_files = get_files_in_pr(repo, pr_number)

    print(f"New Files in PR: {new_files}")
    print(f"Changed files in PR: {modified_files}")

    if not new_files and not modified_files:
        print("No new or modified files found.")
        sys.exit(0)
    else:
        # Check if the files are located in registration/
        
        # Check the namespace in index.json for the plugin
        # namespaces MUST be atomic!
        sys.exit(1)
