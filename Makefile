all:
	@echo ""
	@echo "-------------------------------------------------------------------------------"
	@echo "                             🧠 Laboratorio 3 🧠"
	@echo "             💡 Contenedor de docker para probar ciertas cosas 💡"
	@echo ""
	@echo " ⚠️ NO ES, NI DEBE SER USADO COMO LA MÁQUINA VIRTUAL OFICIAL DE LA MATERIA ⚠️"
	@echo "-------------------------------------------------------------------------------"
	@echo ""
	@echo " make build                             # construir el container"
	@echo " make shell                             # abrir una shell dentro del container"
	@echo ""
	@echo "-------------------------------------------------------------------------------"
	@echo ""

IMAGE_NAME=labo3

build:
	docker compose build service1

shell:
	docker compose run --rm -ti service1 bash

reshell:
	docker compose exec -ti service1 bash
