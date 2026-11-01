# UML баримт (автоматаар үүсгэсэн: `python3 -m constitution.uml`)

## 1. Бүрэлдэхүүн / өгөгдлийн урсгал
```mermaid
flowchart LR
    TXT[(undsen_khuuli_mn.txt<br/>legalinfo lawId=367)] --> P[text_mn.py<br/>parse / modality / delegations]
    P --> Q{{q&#40;pid, phrase&#41;<br/>verbatim guard}}
    A[articles.py<br/>71 articles, TOTAL_SEATS=126] --> C
    M[model.py] -.types.-> A
    PR[procedures.py<br/>8 state machines] --> C[checks.py<br/>rules]
    PR --> S[stress.py<br/>7 scenarios]
    Q --> C
    C --> R[report.py]
    S --> R
    R --> J[out/report.json]
    R --> MD[out/REPORT.md]
    J --> E[explorer/build.py] --> H[out/explorer.html]
    PR --> U[uml.py] --> UM[docs/UML.md + out/uml.html]
```

## 2. Ангийн диаграм (model.py, procedures.py)
```mermaid
classDiagram
    class Article { +str number +int chapter +str title }
    class Provision { +str pid +Kind kind +str actor +bool delegates +str limits +float deadline_days +tuple terms }
    class Threshold { +Fraction fraction +Base base +seats_needed(total) int }
    class Finding { +str rule +str severity +str category +tuple articles +str evidence +str fix }
    class Machine { +str name +str start +dict transitions +dict possible +set must_act }
    class T { +str to +str pid +str actor +float deadline_days +str default_on_timeout }
    class Kind { <<enum>> right duty prohibition power procedure declaration delegation }
    class Base { <<enum>> total present voters }
    Article "1" *-- "many" Provision
    Provision --> Kind
    Provision "0..1" --> Threshold
    Threshold --> Base
    Machine "1" *-- "many" T
    Finding ..> Provision : cites via q()
    Finding ..> Machine : derived from
```

## 3. Тохиолдол: 2025 оны 10-р сар (дараалал)
```mermaid
sequenceDiagram
    autonumber
    actor H as УИХ
    actor P as Ерөнхийлөгч
    participant C as Цэц
    participant M as PM_DISMISSAL machine
    H->>M: vote_majority_total [43.1] 2025-10-17
    M-->>H: DISMISSED
    P->>M: president_veto [33.1.1] 2025-10-20
    M--xP: ✗ UNDEFINED_TRANSITION (DISMISSED, president_veto)
    Note over M,P: 33.1.1 «бусад шийдвэр» хамрах эсэх тодорхойгүй
    H->>C: tsets_petition [66.2.1]
    C->>M: tsets_finds_void [66.4] 2025-10-22
    M-->>H: IN_OFFICE
```

Төлөвт машин бүрийг хоёр давхаргаар: (а) зөвхөн Үндсэн хууль, (б) Үндсэн хууль + хууль. ⚖ — зөвхөн энгийн хуулиар тодорхойлогдсон шилжилт/хугацаа; цэнхэр төлөв — зөвхөн хуульд байдаг; улаан — аль ч давхаргад заагаагүй.

## 4. Төлөвт машин: Ерөнхий сайдыг огцруулах (43, 33.1.1, 22.3, 66)
```mermaid
stateDiagram-v2
    direction LR
    [*] --> IN_OFFICE
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    IN_OFFICE --> MOTION_FILED: motion_by_quarter ‹43.1›
    MOTION_FILED --> DEBATE: debate_after_3_days ‹43.1 ≤3х›
    DEBATE --> DISMISSED: vote_majority_total ‹43.1 ≤10х›
    DEBATE --> IN_OFFICE: vote_fails ‹43.1 ≤10х›
    DISMISSED --> NEW_PM: new_pm_appointed ‹43.1 ≤30х›
    DISMISSED --> DISSOLUTION_DUE: timeout [43.1]
    DISMISSED --> TSETS_REVIEW: tsets_petition ‹66.2.1›
    DISSOLUTION_DUE --> DISSOLVED: president_dissolves ‹22.3›
    TSETS_REVIEW --> IN_OFFICE: tsets_finds_void ‹66.4›
    TSETS_REVIEW --> DISMISSED: tsets_upholds ‹66.4›
    DISMISSED --> DISSOLUTION_DUE: no_pm_in_30_days ‹22.3 ≤30х›
    DEBATE --> UNDEFINED: ✗ no_vote_within_10_days
    DEBATE --> UNDEFINED: ✗ quorum_lost
    DISMISSED --> UNDEFINED: ✗ president_veto
    DISSOLUTION_DUE --> UNDEFINED: ✗ president_does_nothing
    TSETS_REVIEW --> UNDEFINED: ✗ tsets_silent
    note right of DISSOLUTION_DUE: STALL - president_dissolves - хугацаа, анхдагч үр дагаваргүй
    note right of TSETS_REVIEW: STALL - tsets_finds_void - хугацаа, анхдагч үр дагаваргүй
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
```

## 4б. Ерөнхий сайдыг огцруулах (43, 33.1.1, 22.3, 66) + хууль
```mermaid
stateDiagram-v2
    direction LR
    [*] --> IN_OFFICE
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    IN_OFFICE --> MOTION_FILED: motion_by_quarter ‹43.1›
    MOTION_FILED --> DEBATE: debate_after_3_days ‹43.1 ≤3х›
    DEBATE --> DISMISSED: vote_majority_total ‹43.1 ≤10х›
    DEBATE --> IN_OFFICE: vote_fails ‹43.1 ≤10х›
    DISMISSED --> NEW_PM: new_pm_appointed ‹43.1 ≤30х›
    DISMISSED --> DISSOLUTION_DUE: timeout [43.1]
    DISMISSED --> TSETS_REVIEW: tsets_petition ‹66.2.1›
    DISSOLUTION_DUE --> DISSOLVED: president_dissolves ‹22.3›
    TSETS_REVIEW --> IN_OFFICE: tsets_finds_void ‹66.4›
    TSETS_REVIEW --> DISMISSED: tsets_upholds ‹66.4›
    DISMISSED --> DISSOLUTION_DUE: no_pm_in_30_days ‹22.3 ≤30х›
    DISSOLVED --> SNAP_ELECTION: ⚖ snap_election_called ‹⚖ Дэгийн тухай 94.1 ≤10х›
    DEBATE --> UNDEFINED: ✗ no_vote_within_10_days
    DEBATE --> UNDEFINED: ✗ quorum_lost
    DISMISSED --> UNDEFINED: ✗ president_veto
    DISSOLUTION_DUE --> UNDEFINED: ✗ president_does_nothing
    TSETS_REVIEW --> UNDEFINED: ✗ tsets_silent
    note right of DISSOLUTION_DUE: STALL - president_dissolves - хугацаа, анхдагч үр дагаваргүй
    note right of TSETS_REVIEW: STALL - tsets_finds_void - хугацаа, анхдагч үр дагаваргүй
    note left of DEBATE: ⚖ ирц нээлт, санал хураалтад заавал ‹⚖ УИХ-ын тухай 21.5›
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
    class SNAP_ELECTION statute
```

## 5. Төлөвт машин: Итгэл хүлээлгэх (44)
```mermaid
stateDiagram-v2
    direction LR
    [*] --> IN_OFFICE
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    IN_OFFICE --> DEBATE: pm_requests_confidence ‹44.1›
    DEBATE --> IN_OFFICE: passed ‹44.2 ≤13х›
    DEBATE --> DEEMED_RESIGNED: not_passed ‹44.2 ≤13х›
    DEEMED_RESIGNED --> NEW_PM: new_pm_appointed ‹44.2 ≤30х›
    DEEMED_RESIGNED --> DISSOLUTION_DUE: timeout [44.2]
    DEEMED_RESIGNED --> DISSOLUTION_DUE: no_pm_in_30_days ‹22.3 ≤30х›
    DEBATE --> UNDEFINED: ✗ no_vote_within_10_days
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
```

## 6. Төлөвт машин: Засгийн газар бүрдүүлэх (39.2, 22.3)
```mermaid
stateDiagram-v2
    direction LR
    [*] --> AFTER_ELECTION
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    AFTER_ELECTION --> NOMINATED: party_nominates ‹39.2›
    NOMINATED --> SUBMITTED: president_submits_5d ‹39.2 ≤5х›
    SUBMITTED --> PM_APPOINTED: hural_appoints ‹25.1.6 ≤45х›
    SUBMITTED --> DISSOLUTION_DUE: timeout [25.1.6]
    SUBMITTED --> DISSOLUTION_DUE: no_appointment_45d ‹22.3 ≤45х›
    DISSOLUTION_DUE --> DISSOLVED: president_dissolves ‹22.3›
    AFTER_ELECTION --> UNDEFINED: ✗ no_majority_coalition_forms
    NOMINATED --> UNDEFINED: ✗ president_misses_5d
    DISSOLUTION_DUE --> UNDEFINED: ✗ president_does_nothing
    note right of DISSOLUTION_DUE: STALL - president_dissolves - хугацаа, анхдагч үр дагаваргүй
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
```

## 6б. Засгийн газар бүрдүүлэх (39.2, 22.3) + хууль
```mermaid
stateDiagram-v2
    direction LR
    [*] --> AFTER_ELECTION
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    AFTER_ELECTION --> NOMINATED: party_nominates ‹39.2›
    NOMINATED --> SUBMITTED: president_submits_5d ‹39.2 ≤5х›
    SUBMITTED --> PM_APPOINTED: hural_appoints ‹25.1.6 ≤45х›
    SUBMITTED --> DISSOLUTION_DUE: timeout [25.1.6]
    SUBMITTED --> DISSOLUTION_DUE: no_appointment_45d ‹22.3 ≤45х›
    DISSOLUTION_DUE --> DISSOLVED: president_dissolves ‹22.3›
    DISSOLVED --> SNAP_ELECTION: ⚖ snap_election_called ‹⚖ Дэгийн тухай 94.1 ≤10х›
    AFTER_ELECTION --> UNDEFINED: ✗ no_majority_coalition_forms
    NOMINATED --> UNDEFINED: ✗ president_misses_5d
    DISSOLUTION_DUE --> UNDEFINED: ✗ president_does_nothing
    note right of DISSOLUTION_DUE: STALL - president_dissolves - хугацаа, анхдагч үр дагаваргүй
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
    class SNAP_ELECTION statute
```

## 7. Төлөвт машин: Ерөнхийлөгчийн хориг (33.1.1)
```mermaid
stateDiagram-v2
    direction LR
    [*] --> LAW_PASSED
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    LAW_PASSED --> VETOED: president_vetoes ‹33.1.1›
    LAW_PASSED --> IN_FORCE: president_accepts ‹26.3›
    VETOED --> IN_FORCE: override_2_3_present ‹33.1.1›
    VETOED --> DEAD: veto_accepted ‹33.1.1›
    LAW_PASSED --> UNDEFINED: ✗ president_silent
    VETOED --> UNDEFINED: ✗ hural_never_considers
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
```

## 7б. Ерөнхийлөгчийн хориг (33.1.1) + хууль
```mermaid
stateDiagram-v2
    direction LR
    [*] --> LAW_PASSED
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    LAW_PASSED --> VETOED: president_vetoes ‹33.1.1, ⚖ Дэгийн тухай 46.5 ≤5 ажлын өдөр›
    LAW_PASSED --> IN_FORCE: president_accepts ‹26.3›
    VETOED --> IN_FORCE: override_2_3_present ‹33.1.1, ⚖ Дэгийн тухай 90.1 ≤14 ажлын өдөр›
    VETOED --> DEAD: veto_accepted ‹33.1.1, ⚖ Дэгийн тухай 90.1 ≤14 ажлын өдөр›
    VETOED --> IN_FORCE: ⚖ override_fails ‹⚖ Дэгийн тухай 46.6 ≤14 ажлын өдөр›
    LAW_PASSED --> UNDEFINED: ✗ president_silent
    VETOED --> UNDEFINED: ✗ hural_never_considers
    note left of VETOED: ⚖ хориг хэлэлцэгдэх хүртэл хууль түр зогсоно ‹⚖ УИХ-ын тухай 5.4›
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
```

## 8. Төлөвт машин: Онц/дайны байдал (25.1.18, 33.1.12, 19.2)
```mermaid
stateDiagram-v2
    direction LR
    [*] --> NORMAL
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    NORMAL --> EMERGENCY: hural_declares ‹25.1.18›
    NORMAL --> PRES_DECREE: president_declares_in_recess ‹33.1.12›
    PRES_DECREE --> EMERGENCY: hural_approves_7d ‹33.1.12 ≤7х›
    PRES_DECREE --> NORMAL: timeout [33.1.12]
    PRES_DECREE --> NORMAL: hural_silent_7d ‹33.1.12 ≤7х›
    PRES_DECREE --> NORMAL: hural_rejects ‹33.1.12 ≤7х›
    EMERGENCY --> NORMAL: hural_lifts ‹25.1.18›
    EMERGENCY --> HURAL_HOLDS_OVER: regular_election_due ‹22.1›
    HURAL_HOLDS_OVER --> NORMAL: hural_lifts ‹22.1›
    EMERGENCY --> UNDEFINED: ✗ max_duration_reached
    HURAL_HOLDS_OVER --> UNDEFINED: ✗ max_duration_reached
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
```

## 8б. Онц/дайны байдал (25.1.18, 33.1.12, 19.2) + хууль
```mermaid
stateDiagram-v2
    direction LR
    [*] --> NORMAL
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    NORMAL --> EMERGENCY: hural_declares ‹25.1.18›
    NORMAL --> PRES_DECREE: president_declares_in_recess ‹33.1.12›
    PRES_DECREE --> EMERGENCY: hural_approves_7d ‹33.1.12 ≤7х›
    PRES_DECREE --> NORMAL: timeout [33.1.12]
    PRES_DECREE --> NORMAL: hural_silent_7d ‹33.1.12 ≤7х›
    PRES_DECREE --> NORMAL: hural_rejects ‹33.1.12 ≤7х›
    EMERGENCY --> NORMAL: hural_lifts ‹25.1.18›
    EMERGENCY --> HURAL_HOLDS_OVER: regular_election_due ‹22.1›
    HURAL_HOLDS_OVER --> NORMAL: hural_lifts ‹22.1›
    EMERGENCY --> NORMAL: ⚖ end_date_reached ‹⚖ Онц байдлын тухай 5.7›
    EMERGENCY --> EMERGENCY: ⚖ nsc_extension ‹⚖ Онц байдлын тухай 6.2›
    EMERGENCY --> NORMAL: ⚖ nsc_early_end ‹⚖ Онц байдлын тухай 6.3›
    HURAL_HOLDS_OVER --> NORMAL: ⚖ end_date_reached ‹⚖ Онц байдлын тухай 5.7›
    HURAL_HOLDS_OVER --> HURAL_HOLDS_OVER: ⚖ nsc_extension ‹⚖ Онц байдлын тухай 6.2›
    EMERGENCY --> UNDEFINED: ✗ max_duration_reached
    HURAL_HOLDS_OVER --> UNDEFINED: ✗ max_duration_reached
    note left of EMERGENCY: ⚖ онц байдлын үед Үндсэн хуулийг өөрчлөхгүй ‹⚖ Онц байдлын тухай 19›
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
```

## 9. Төлөвт машин: Цэцийн хяналт (66)
```mermaid
stateDiagram-v2
    direction LR
    [*] --> PETITION
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    PETITION --> HEARING: tsets_accepts_case ‹66.1›
    HEARING --> CONCLUSION: conclusion_issued ‹66.2›
    CONCLUSION --> RESOLVED: hural_accepts ‹66.4›
    CONCLUSION --> RE_REVIEW: hural_rejects ‹66.3›
    RE_REVIEW --> RESOLVED: final_decision ‹66.3›
    PETITION --> UNDEFINED: ✗ tsets_ignores_petition
    HEARING --> UNDEFINED: ✗ tsets_silent
    CONCLUSION --> UNDEFINED: ✗ hural_never_considers
    RE_REVIEW --> UNDEFINED: ✗ tsets_silent
    note right of CONCLUSION: STALL - hural_accepts - хугацаа, анхдагч үр дагаваргүй
    note right of RE_REVIEW: STALL - final_decision - хугацаа, анхдагч үр дагаваргүй
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
```

## 9б. Цэцийн хяналт (66) + хууль
```mermaid
stateDiagram-v2
    direction LR
    [*] --> PETITION
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    PETITION --> HEARING: tsets_accepts_case ‹66.1, ⚖ Цэцийн ажиллагааны тухай 21.2 ≤14х›
    HEARING --> CONCLUSION: conclusion_issued ‹66.2›
    CONCLUSION --> RESOLVED: hural_accepts ‹66.4, ⚖ Цэцийн ажиллагааны тухай 35.2 ≤15х›
    CONCLUSION --> RE_REVIEW: hural_rejects ‹66.3, ⚖ Цэцийн ажиллагааны тухай 35.2 ≤15х›
    RE_REVIEW --> RESOLVED: final_decision ‹66.3›
    PETITION --> REFUSED: ⚖ tsets_refuses ‹⚖ Цэцийн ажиллагааны тухай 21.5 ≤14х›
    HEARING --> HEARING: ⚖ tie_vote ‹⚖ Цэцийн ажиллагааны тухай 29.6 ≤30х›
    RE_REVIEW --> RESOLVED: ⚖ no_two_thirds ‹⚖ Цэцийн ажиллагааны тухай 3.6›
    PETITION --> UNDEFINED: ✗ tsets_ignores_petition
    HEARING --> UNDEFINED: ✗ tsets_silent
    CONCLUSION --> UNDEFINED: ✗ hural_never_considers
    RE_REVIEW --> UNDEFINED: ✗ tsets_silent
    note right of RE_REVIEW: STALL - final_decision - хугацаа, анхдагч үр дагаваргүй
    note left of CONCLUSION: ⚖ эцсийн шийдвэр хүртэл заалт түдгэлзэнэ ‹⚖ Цэцийн ажиллагааны тухай 32.4›
    note left of RE_REVIEW: ⚖ эцсийн шийдвэр хүртэл заалт түдгэлзэнэ ‹⚖ Цэцийн ажиллагааны тухай 32.4›
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
    class REFUSED statute
```

## 10. Төлөвт машин: Ерөнхийлөгчийн сонгууль (31, 32.1, 30.2)
```mermaid
stateDiagram-v2
    direction LR
    [*] --> ROUND_1
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    ROUND_1 --> ELECTED: majority ‹31.4›
    ROUND_1 --> ROUND_2: no_majority ‹31.5›
    ROUND_2 --> ELECTED: majority ‹31.5›
    ROUND_2 --> ROUND_1: no_majority ‹31.6›
    ELECTED --> OATH: hural_recognizes ‹31.4›
    OATH --> NEW_PRESIDENT: oath_30d ‹32.2 ≤30х›
    ELECTED --> UNDEFINED: ✗ hural_delays_recognition
    note right of ELECTED: STALL - hural_recognizes - хугацаа, анхдагч үр дагаваргүй
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
```

## 11. Төлөвт машин: Үндсэн хуульд нэмэлт өөрчлөлт (68, 69)
```mermaid
stateDiagram-v2
    direction LR
    [*] --> DRAFT
    state "НӨХЦӨЛ ТОДОРХОЙГҮЙ" as UNDEFINED
    DRAFT --> ADOPTED: vote_3_4_total ‹69.1›
    DRAFT --> FROZEN: fails_twice ‹69.2›
    DRAFT --> REFERENDUM: referendum_2_3 ‹68.2›
    REFERENDUM --> ADOPTED: valid_majority ‹25.1.16›
    FROZEN --> DRAFT: new_composition ‹69.2›
    DRAFT --> UNDEFINED: ✗ within_6m_of_snap_election
    classDef bad fill:#fdd,stroke:#c00,color:#900
    classDef statute fill:#e6f0ff,stroke:#3366cc,color:#123
    class UNDEFINED bad
```
