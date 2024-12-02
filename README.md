# Simulazione del Decadimento della Particella K\*⁰

**Autori**: Malagoli Tommaso Andrea, Mazzi Davide, Pivi Riccardo, Schirripa Mattia  
**Data**: Novembre 2024  

## Introduzione

Questo progetto simula eventi fisici risultanti da collisioni di particelle elementari.  
Il codice, scritto in C++, utilizza la libreria ROOT per analisi dati e generazione di grafici.  

Consultare la relazione presente nella repository per maggiori chiarimenti sul codice e sui risultati della simulazione.

## Struttura del Codice

Il programma implementa tre classi principali:  

1. **ParticleType**  
   - Descrive massa, carica e nome delle particelle elementari.  

2. **ResonanceType**  
   - Estende `ParticleType` includendo la larghezza di risonanza.  

3. **Particle**  
   - Descrive quantità di moto e include un array di puntatori a `ParticleType`.  

### Gerarchia delle Classi

- `ResonanceType` eredita da `ParticleType` e sovrascrive il metodo `Print()`.  
- `Particle` utilizza una relazione *has-a* con `ParticleType`.  

## Generazione degli Eventi
- La generazione è svilta dal file `main_module.cpp`.
- Generati \(10^5\) eventi totali.  
- Ogni evento contiene almeno 100 particelle.  
- Distribuzione delle particelle secondo le probabilità specificate:  

| Particella | Probabilità (%) |
|------------|-----------------|
| π⁺         | 40             |
| π⁻         | 40             |
| k⁺         | 5              |
| k⁻         | 5              |
| p⁺         | 4.5            |
| p⁻         | 4.5            |
| K\*⁰       | 1              |

Le particelle sono generate stocasticamente utilizzando il metodo Monte Carlo di ROOT.

## Come Eseguire il Progetto

1. Clona questo repository.  
2. Assicurati che il file `compile.sh` abbia i permessi di esecuzione:
   ```bash
   chmod +x compile.sh
3. Per compilare (questo comando aprirà anche root):
   ```bash
   ./compile.sh
4. Per eseguire la generazione:
   ```bash
   main_module();
5. Per eseguire l'analisi:
   ```bash
   macro_analysis();


/*This is a try
in Particle.hpp l'array P permette di usare gli algoritmi
NON usare std::vector nel vettore grande*/
