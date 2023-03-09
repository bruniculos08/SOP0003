from datetime import datetime

# result = abs(datetime.strptime("2022-07-30", "%Y-%m-%d").date() - datetime.strptime("2022-03-28", "%Y-%m-%d").date())
# result = abs(datetime.strptime("2022-12-17", "%Y-%m-%d").date() - datetime.strptime("2022-08-15", "%Y-%m-%d").date())
# result = abs(datetime.strptime("2023-07-07", "%Y-%m-%d").date() - datetime.strptime("2023-02-27", "%Y-%m-%d").date())
# result = abs(datetime.strptime("2022-07-28", "%Y-%m-%d").date() - datetime.strptime("2022-03-28", "%Y-%m-%d").date())
result = abs(datetime.strptime("2022-07-23", "%Y-%m-%d").date() - datetime.strptime("2022-03-28", "%Y-%m-%d").date())
# months = int(result/30)
# days = result%30
string = f"Faltam {abs(int(result.days/30))} meses e {result.days%30} dias para o fim do semestre na UDESC."
print(string)